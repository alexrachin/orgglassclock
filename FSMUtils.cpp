#include <stdint.h>
#include "FSMUtils.h"

void setSegment(uint8_t *timeSegment, byte *buf, long *colorBuf, int i, long color) {
    buf[i*2]= (*timeSegment)/10; colorBuf[i*2] = color;
    buf[i*2+1]= (*timeSegment)%10; colorBuf[i*2+1] = color;
}

void clearSegment(int i, long *colorBuf) {
    colorBuf[i*2] = noneColor;colorBuf[i*2+1] = noneColor;
}

void setMonth(Time *t, byte *buf, long *colorBuf) {
    setSegment(&(t->mon),buf, colorBuf, CLOCK_FIRST_HALF, monthColor);
}

void setDay(Time *t, byte *buf, long *colorBuf) {
    setSegment(&(t->date),buf, colorBuf, CLOCK_SECOND_HALF, dayColor);
}

void setHour(Time *t, byte *buf, long *colorBuf) {
    setSegment(&(t->hour),buf, colorBuf, CLOCK_FIRST_HALF, hourColor);
}

void setMinute(Time *t, byte *buf, long *colorBuf) {
    setSegment(&(t->min),buf, colorBuf, CLOCK_SECOND_HALF, minuteColor);
}

void displayMonthsDays(Time *time, byte *buf, long *colorBuf) {
    setMonth(time, buf, colorBuf);
    setDay(time, buf, colorBuf);
}

void displayHoursMinutes(Time *time, byte *buf, long *colorBuf) {
    setHour(time, buf, colorBuf);
    setMinute(time, buf, colorBuf);
}
void displayHoursAdjust(Time *time, byte *buf, long *colorBuf) {
    setHour(time, buf, colorBuf);
    clearSegment(CLOCK_SECOND_HALF, colorBuf);
}
void displayMinutesAdjust(Time *time, byte *buf, long *colorBuf) {
    clearSegment(CLOCK_FIRST_HALF, colorBuf);
    setMinute(time, buf, colorBuf);
}
void displayMonthsAdjust(Time *time, byte *buf, long *colorBuf) {
    setMonth(time, buf, colorBuf);
    clearSegment(CLOCK_SECOND_HALF, colorBuf);
}
void displayDaysAdjust(Time *time, byte *buf, long *colorBuf) {
    clearSegment(CLOCK_FIRST_HALF, colorBuf);
    setDay(time, buf, colorBuf);
}

void incNum(unsigned char *buf, int half, int limit) {
    int number = buf[0+half*2] * 10 + buf[1+half*2];
    if (number < limit) {
        number++;
    } else {
        number = 0;
    }
    buf[0+half*2] = (unsigned char) (number / 10);
    buf[1+half*2] = (unsigned char) (number % 10);
}

void decNum(unsigned char *buf, int half) {
    int number = buf[0+half*2] * 10 + buf[1+half*2];
    if (number > 0) {
        number--;
    } else {
        number = 0;
    }
    buf[0+half*2] = (unsigned char) (number / 10);
    buf[1+half*2] = (unsigned char) (number % 10);
}

void incHours(Time *time, byte *buf, long *colorBuf) {
    incNum(buf, CLOCK_FIRST_HALF, 23);
}
void decHours(Time *time, byte *buf, long *colorBuf) {
    decNum(buf, CLOCK_FIRST_HALF);
}
void incMinutes(Time *time, byte *buf, long *colorBuf) {
    incNum(buf, CLOCK_SECOND_HALF, 59);
}
void decMinutes(Time *time, byte *buf, long *colorBuf) {
    decNum(buf, CLOCK_SECOND_HALF);
}
void incMonths(Time *time, byte *buf, long *colorBuf) {
    incNum(buf, CLOCK_FIRST_HALF, 11);
}
void decMonths(Time *time, byte *buf, long *colorBuf) {
    decNum(buf, CLOCK_FIRST_HALF);
}
void incDays(Time *time, byte *buf, long *colorBuf) {
    incNum(buf, CLOCK_SECOND_HALF, 31);
}
void decDays(Time *time, byte *buf, long *colorBuf) {
    decNum(buf, CLOCK_SECOND_HALF);
}
