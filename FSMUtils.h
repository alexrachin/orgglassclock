#include "DS1302.h"

#ifndef FSM_UTILS
#define FSM_UTILS

#define byte unsigned char
#define uint8_t unsigned char
#define hourColor 0xFF0045
#define minuteColor 0xF000F6
#define monthColor 0x00F0F6
#define dayColor 0x00FF45
#define noneColor 0x0

#define CLOCK_FIRST_HALF 0
#define CLOCK_SECOND_HALF 1

enum Mode {
    HoursMinutes, MonthsDays, HoursAdjust, MinutesAdjust, MonthsAdjust, DaysAdjust
};

enum Act {
    PerTime, ModeButtonSignal, UpButtonSignal, DownButtonSignal
};

struct Transition {
    enum Mode mode;
    void (*onStateAction)(Time *time, byte *buf, long *colorBuf);
};

void setSegment(uint8_t *timeSegment, byte *buf, long *colorBuf, int i, long color);
void displayMonthsDays(Time *time, byte *numBuf, long *colorBuf);
void displayHoursMinutes(Time *time, byte *numBuf, long *colorBuf);
void displayHoursAdjust(Time *time, byte *numBuf, long *colorBuf);
void displayMinutesAdjust(Time *time, byte *numBuf, long *colorBuf);
void displayMonthsAdjust(Time *time, byte *numBuf, long *colorBuf);
void displayDaysAdjust(Time *time, byte *numBuf, long *colorBuf);
void incHours(Time *time, byte *numBuf, long *colorBuf);
void decHours(Time *time, byte *numBuf, long *colorBuf);
void incMinutes(Time *time, byte *numBuf, long *colorBuf);
void decMinutes(Time *time, byte *numBuf, long *colorBuf);
void incMonths(Time *time, byte *numBuf, long *colorBuf);
void decMonths(Time *time, byte *numBuf, long *colorBuf);
void incDays(Time *time, byte *numBuf, long *colorBuf);
void decDays(Time *time, byte *numBuf, long *colorBuf);

#endif
