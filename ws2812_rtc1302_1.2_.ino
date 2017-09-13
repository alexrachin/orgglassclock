#include "FastLED.h"
#include <DS1302.h>
#include <Thread.h>

#define NUM_LEDS 41
#define DATA_PIN 10

byte position[] = {5,4,6,3,7,2,8,1,9,0};

handler modeHandler {
  14,LOW,LOW, Thread()
};
handler upHandler {
  15,LOW,LOW, Thread()
};
handler downHandler {
  16,LOW,LOW, Thread()
};

int modeButton = 14; boolean lastModeButtonState = false;boolean currModeButtonState = false;
Thread modeButtDebounce = Thread();
int upButton = 15; boolean lastUpButtonState = false;boolean currUpButtonState = false;
Thread upButtDebounce = Thread();
int downButton = 16; boolean lastDownButtonState = false;boolean currDownButtonState = false;
Thread downButtDebounce = Thread();
Thread timeElapseThread = Thread();

enum Mode currMode = HoursMinutes;
enum Act currentSignal;

CRGB leds[NUM_LEDS];
boolean point = true;
byte num[] = {0,0,0,0};
long numColor[]= {0xFFFFFF,0xFFFFFF,0xFFFFFF,0xFFFFFF};
DS1302 rtc(11, 12, 13);
Time  t;
char temp = 0;
int displayTimeSwitcher = 0;

void setup() {
  Serial.begin(9600);
  Serial.println("Hello");
  FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS);
  pinMode(modeButton, INPUT);
  pinMode(upButton, INPUT);
  pinMode(downButton, INPUT);
  
  rtc.setDOW(WEDNESDAY);
  rtc.setTime(21, 54, 0);
  rtc.setDate(13, 9, 2017);
  rtc.halt(false);

  modeButtDebounce.onRun(...);
  modeButtDebounce.setInterval(10);
  upButtDebounce.onRun(...);
  upButtDebounce.setInterval(10);
  downButtDebounce.onRun(...);
  downButtDebounce.setInterval(10);
  timeElapseThread.onRun(...);
  timeElapseThread.setInterval(10000);
}

void callback() {
  if (debouncing(modeButton)) {
    displayTimeSwitcher = 0;
    FSMwork(ModeButtonSignal);
  }
}

void drawNumber(byte shift, byte value, CRGB color){
  for(int i=0; i<10; i++){
    if (i==position[value]){
      leds[shift+i] = color;
    } else {
      leds[shift+i]=0;
    }
  }
}

void redraw(){
  drawNumber(0, num[0], numColor[0]);
  drawNumber(10, num[1], numColor[1]);
  drawNumber(21, num[2], numColor[2]);
  drawNumber(31, num[3], numColor[3]);
  if (point){
    leds[20]=0x00ff00;
  } else {
    leds[20]=0x0;
  }
}

boolean debouncing(int buttonPin) {
  boolean buttonCurrentState = digitalRead(buttonPin);
  if (buttonCurrentState == true) {
    delay(5);
    return digitalRead(buttonPin);
  }
  return false;
}

void loop() {

    checkButt(modeHandler);
    checkButt(upHandler);
    checkButt(downHandler);

    t = rtc.getTime();
    Serial.print(t.year);Serial.print("-");Serial.print(t.mon);Serial.print("-");Serial.print(t.date);Serial.print(" ");
    Serial.print(t.hour);Serial.print(":");Serial.print(t.min);Serial.print(":");Serial.print(t.sec);Serial.print("\n");

    if(displayTimeSwitcher == 15) {
    displayTimeSwitcher = 0;
    FSMwork(PerTime);
    }
    displayTimeSwitcher++;
    if((currMode == HoursMinutes)||(currMode == MonthsDays)) {
    point = !point;
    } else {
    point = true;
    }
    redraw();
    FastLED.show();
    delay(1000);
}

