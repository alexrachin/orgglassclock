#include <cstdio>
#include "Arduino.h"
#include "FSMUtils.h"



Transition displayMonthsDays() {
    num[0]=t.mon%10;numColor[0]=0x00FF00;
    num[1]=t.mon/10;numColor[1]=0x00FF00;
    num[2]=t.date/10;numColor[2]=0x8D5104;
    num[3]=t.date%10;numColor[3]=0x8D5104;
}
Transition displayHoursMinutes() {
    num[0]=t.hour%10;numColor[0]=0xFF0000;
    num[1]=t.hour/10;numColor[1]=0xFF0000;
    num[2]=t.min/10;numColor[2]=0xF000F6;
    num[3]=t.min%10;numColor[3]=0xF000F6;
}
Transition displayHoursAdjust() {
    num[0]=t.hour%10;numColor[0]=0xFF0000;
    num[1]=t.hour/10;numColor[1]=0xFF0000;
    num[2]=t.min/10;numColor[2]=0x0;
    num[3]=t.min%10;numColor[3]=0x0;
}
Transition displayMinutesAdjust() {
    num[0]=t.hour%10;numColor[0]=0x0;
    num[1]=t.hour/10;numColor[1]=0x0;
    num[2]=t.min/10;numColor[2]=0xF000F6;
    num[3]=t.min%10;numColor[3]=0xF000F6;
}
Transition displayMonthsAdjust() {
    num[0]=t.mon%10;numColor[0]=0x00FF00;
    num[1]=t.mon/10;numColor[1]=0x00FF00;
    num[2]=t.date/10;numColor[2]=0x0;
    num[3]=t.date%10;numColor[3]=0x0;
}
Transition displayDaysAdjust() {
    num[0]=t.mon%10;numColor[0]=0x0;
    num[1]=t.mon/10;numColor[1]=0x0;
    num[2]=t.date/10;numColor[2]=0x8D5104;
    num[3]=t.date%10;numColor[3]=0x8D5104;
}
Transition incHours() {
    printf("xx + 1 Hours\n");
}
Transition decHours() {
    printf("xx - 1 Hours\n");
}
Transition incMinutes() {
    printf("xx + 1 Minutes\n");
}
Transition decMinutes() {
    printf("xx - 1 Minutes\n");
}
Transition incMonths() {
    printf("xx + 1 Months\n");
}
Transition decMonths() {
    printf("xx - 1 Months\n");
}
Transition incDays() {
    printf("xx + 1 Days\n");
}
Transition decDays() {
    printf("xx - 1 Days\n");
}

void FSMwork(Mode currMode, Act s) {
    currMode = FSM_table[currMode][s].mode;
}