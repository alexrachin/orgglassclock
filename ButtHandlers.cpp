#include "Arduino.h"
#include "ButtHandlers.h"


void checkButt(Handler h) {
    h.currButtonState = digitalRead(h.buttonPin);
    if (h.currButtonState != h.lastButtonState) {
        if(h.buttonDebounce.shouldRun())
            h.buttonDebounce.run();
    }
}

void doHand(Handler h,transition_callback func) {
    if(h.currButtonState != h.lastButtonState) {
        h.lastButtonState = h.currButtonState;
        if(h.lastButtonState == HIGH) {
            func();
        }
    }
}