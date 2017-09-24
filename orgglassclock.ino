#include "FastLED.h"
#include <DS1302.h>
#include <Thread.h>
#include "FSMUtils.h"

#define NUM_LEDS 41
#define DATA_PIN 10
#define MODE_BUTTON 14
#define UP_BUTTON 15
#define DOWN_BUTTON 16

#define CHANGE_MODE_TIME 10
#define FORSE_CHANGE_MODE_TIME 50

byte position[] = {5, 4, 6, 3, 7, 2, 8, 1, 9, 0}; // util helps to count in correct order

struct Handler {
  int buttonPin;
  int currButtonState;
  int lastButtonState;
  Act action;
  Thread buttonDebounce;
};

struct Transition FSM_table[6][4] = {
  {{MonthsDays, displayMonthsDays}, {MonthsDays, displayMonthsDays}, {HoursMinutes, NULL}, {HoursMinutes, NULL}},
  {{HoursMinutes, displayHoursMinutes}, {HoursAdjust, displayHoursAdjust}, {MonthsDays, NULL}, {MonthsDays, NULL}},
  {{HoursMinutes, displayHoursMinutes}, {MinutesAdjust, displayMinutesAdjust}, {HoursAdjust, incHours}, {HoursAdjust, decHours}},
  {{HoursMinutes, displayHoursMinutes}, {MonthsAdjust, displayMonthsAdjust}, {MinutesAdjust, incMinutes}, {MinutesAdjust, decMinutes}},
  {{HoursMinutes, displayHoursMinutes}, {DaysAdjust, displayDaysAdjust}, {MonthsAdjust, incMonths}, {MonthsAdjust, decMonths}},
  {{HoursMinutes, displayHoursMinutes}, {HoursMinutes, displayHoursMinutes}, {DaysAdjust, incDays}, {DaysAdjust, decDays}}
};

Handler modeHandler {
  MODE_BUTTON, LOW, LOW, ModeButtonSignal, Thread()
};
Handler upHandler {
  UP_BUTTON, LOW, LOW, UpButtonSignal, Thread()
};
Handler downHandler {
  DOWN_BUTTON, LOW, LOW, DownButtonSignal, Thread()
};

Thread timeElapseThread = Thread(); //triggered every second

Transition currentState = FSM_table[HoursMinutes][PerTime];
CRGB leds[NUM_LEDS];
boolean colon = true; //colon between segments in the clock
byte num[] = {0, 0, 0, 0}; // number to highlight in each of four orgglass segments
long numColor[] = {0xFFFFFF, 0xFFFFFF, 0xFFFFFF, 0xFFFFFF}; //colors of each of 4 segments
DS1302 rtc(11, 12, 13);
Time t;
char downtimeCounter = 0; //change more every CHANGE_MODE_TIME
int buttonUnderstander = 0; //to understand which button has been pressed
boolean singleTriggering = false; //to trigger one time per one press
int timeToChange[] = {CHANGE_MODE_TIME,CHANGE_MODE_TIME,FORSE_CHANGE_MODE_TIME,
                      FORSE_CHANGE_MODE_TIME,FORSE_CHANGE_MODE_TIME,FORSE_CHANGE_MODE_TIME};

void setup() {
//  Serial.begin(9600);
//  Serial.println("Hello  ");
  FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS);
  pinMode(MODE_BUTTON, INPUT);
  pinMode(UP_BUTTON, INPUT);
  pinMode(DOWN_BUTTON, INPUT);

  rtc.writeProtect(false);

  modeHandler.buttonDebounce.enabled = false;
  modeHandler.buttonDebounce.onRun(doHand);
  modeHandler.buttonDebounce.setInterval(5);
  upHandler.buttonDebounce.enabled = false;
  upHandler.buttonDebounce.onRun(doHand);
  upHandler.buttonDebounce.setInterval(5);
  downHandler.buttonDebounce.enabled = false;
  downHandler.buttonDebounce.onRun(doHand);
  downHandler.buttonDebounce.setInterval(5);
  timeElapseThread.onRun(refresh);
  timeElapseThread.setInterval(1000);
}

void refresh() {
  if((currentState.mode == HoursMinutes) || (currentState.mode == MonthsDays)) {
    colon = !colon;
    downtimeCounter++;
    if (downtimeCounter == timeToChange[currentState.mode]) {
      currentState = FSM_table[currentState.mode][PerTime];
      downtimeCounter = 0;
    }
    currentState.onStateAction(&rtc.getTime(), num, numColor);
    redraw();
    FastLED.show();
  }
}

void drawNumber(byte shift, byte value, CRGB color) {
  for (int i = 0; i < 10; i++) {
    if (i == position[value]) {
      leds[shift + i] = color;
    } else {
      leds[shift + i] = 0;
    }
  }
}

void redraw() {
  drawNumber(0, num[0], numColor[0]);
  drawNumber(10, num[1], numColor[1]);
  drawNumber(21, num[2], numColor[2]);
  drawNumber(31, num[3], numColor[3]);
  if (colon) {
    leds[20] = 0x999999;
  } else {
    leds[20] = 0x0;
  }
}

void loop() { //main func
  checkButt(modeHandler);
  checkButt(upHandler);
  checkButt(downHandler);

  if (timeElapseThread.shouldRun())
    timeElapseThread.run();
}

void checkButt(Handler& h) {
  h.currButtonState = digitalRead(h.buttonPin);
  if (h.currButtonState != h.lastButtonState) {
    h.buttonDebounce.enabled = true;
    buttonUnderstander = h.buttonPin;
    if (h.buttonDebounce.shouldRun()) {
      h.buttonDebounce.run();
    }
  }
}

Handler* getHandler() {
  Handler* ptr;

  if (buttonUnderstander == modeHandler.buttonPin) {
    ptr = &modeHandler;
  } else if (buttonUnderstander == upHandler.buttonPin) {
    ptr = &upHandler;
  } else if (buttonUnderstander == downHandler.buttonPin) {
    ptr = &downHandler;
  } else {
    return;
  }
  return ptr;
}

void setUpTimeSegment() {
  Time timeNow = rtc.getTime();
  if(currentState.mode == HoursAdjust) {
    rtc.setTime(convertToUint8t(num[0], num[1]), timeNow.min, timeNow.sec);
  } else if (currentState.mode == MinutesAdjust) {
    rtc.setTime(timeNow.hour, convertToUint8t(num[2], num[3]), timeNow.sec);
  } else if (currentState.mode == MonthsAdjust) {
    rtc.setDate(timeNow.date, convertToUint8t(num[0], num[1]), timeNow.year);
  } else if (currentState.mode == DaysAdjust) {
    rtc.setDate(convertToUint8t(num[2], num[3]), timeNow.mon, timeNow.year);
  }
}

uint8_t convertToUint8t(byte tens, byte ones) {
  return (tens*10)+ones;
}

void doHand() {
  
  Handler& h = *(getHandler());

  h.currButtonState = digitalRead(h.buttonPin);
  if (h.currButtonState != h.lastButtonState) {
    h.lastButtonState = h.currButtonState;
    if (h.lastButtonState == HIGH) {
      if (singleTriggering == false) {
        if(h.action == ModeButtonSignal) {setUpTimeSegment();}
        currentState = FSM_table[currentState.mode][h.action];
        currentState.onStateAction(&rtc.getTime(), num, numColor);
        redraw();
        FastLED.show();
        singleTriggering = true;
      }
    } else {
      singleTriggering = false;
    }
  }
  buttonUnderstander = 0;
  h.buttonDebounce.enabled = false;
}

