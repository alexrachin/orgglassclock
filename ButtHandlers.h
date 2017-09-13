
#ifndef FSM_UTILS
#define FSM_UTILS

#include <Thread.h>

struct Handler {
    int buttonPin;
    int currButtonState;
    int lastButtonState;
    Thread buttonDebounce;
};



#endif
