#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <afxres.h>
#include <pthread.h>

enum Mode {
    HoursMinutes, MonthsDays, HoursAdjust, MinutesAdjust, MonthsAdjust, DaysAdjust
};

enum Signal {
    PerTime, ModeButtonSignal, UpButtonSignal, DownButtonSignal
};

typedef void (*transition_callback)();

struct transition
{
    enum Mode mode;
    transition_callback worker;
};

void displayMonthsDays() {
    printf("xx month - xx days\n");
}
void displayHoursMinutes() {
    printf("xx hours - xx minutes\n");
}
void displayHoursAdjust() {
    printf("adjust hours\n");
}
void displayMinutesAdjust() {
    printf("adjust minutes\n");
}
void displayMonthsAdjust() {
    printf("adjust months\n");
}
void displayDaysAdjust() {
    printf("adjust days\n");
}
void incHours() {
    printf("xx + 1 Hours\n");
}
void decHours() {
    printf("xx - 1 Hours\n");
}
void incMinutes() {
    printf("xx + 1 Minutes\n");
}
void decMinutes() {
    printf("xx - 1 Minutes\n");
}
void incMonths() {
    printf("xx + 1 Months\n");
}
void decMonths() {
    printf("xx - 1 Months\n");
}
void incDays() {
    printf("xx + 1 Days\n");
}
void decDays() {
    printf("xx - 1 Days\n");
}

void displayMonthsDays();
void displayHoursMinutes();
void displayHoursAdjust();
void displayMinutesAdjust();
void displayMonthsAdjust();
void displayDaysAdjust();
void incHours();
void decHours();
void incMinutes();
void decMinutes();
void incMonths();
void decMonths();
void incDays();
void decDays();

struct transition FSM_table[6][4] = {
        {{MonthsDays, displayMonthsDays},{MonthsDays, displayMonthsDays},{HoursMinutes, NULL},{HoursMinutes, NULL}},
        {{HoursMinutes, displayHoursMinutes},{HoursAdjust, displayHoursAdjust},{MonthsDays, NULL},{MonthsDays, NULL}},
        {{HoursMinutes, displayHoursMinutes},{MinutesAdjust, displayMinutesAdjust},{HoursAdjust, incHours},{HoursAdjust, decHours}},
        {{HoursMinutes, displayHoursMinutes},{MonthsAdjust, displayMonthsAdjust},{MinutesAdjust, incMinutes},{MinutesAdjust, decMinutes}},
        {{HoursMinutes, displayHoursMinutes},{DaysAdjust, displayDaysAdjust},{MonthsAdjust, incMonths},{MonthsAdjust, decMonths}},
        {{HoursMinutes, displayHoursMinutes},{HoursMinutes, displayHoursMinutes},{DaysAdjust, incDays},{DaysAdjust, decDays}}
};

enum Signal currentSignal;
enum Mode currentState = HoursMinutes;
int timeInterval = 0;
int i;

void *myThreadFun(void *vargp) {
    sleep(1);
    printf("Another Thread ---------------------- \n");
    return NULL;
}

int main() {
    pthread_t tid;
    pthread_create(&tid, NULL, myThreadFun, (void *)i);
    while(TRUE) {

        if (timeInterval == 10) {
            timeInterval = 0;
            doFSMWork(currentState, PerTime);
        }
        timeInterval++;
        sleep(1);
    }
}

void doFSMWork(enum Mode currState, enum Signal currSignal) {

    enum Mode newState = FSM_table[currState][currSignal].mode;
    transition_callback worker = FSM_table[currState][currSignal].worker;
    if (worker != NULL) {
        worker();
    }
    currentState = newState;
}