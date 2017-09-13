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

struct Transition displayMonthsDays() {
    printf("xx month - xx days\n");
}
struct Transition displayHoursMinutes() {
    printf("xx hours - xx minutes\n");
}
struct Transition displayHoursAdjust() {
    printf("adjust hours\n");
}
struct Transition displayMinutesAdjust() {
    printf("adjust minutes\n");
}
struct Transition displayMonthsAdjust() {
    printf("adjust months\n");
}
struct Transition displayDaysAdjust() {
    printf("adjust days\n");
}
struct Transition incHours() {
    printf("xx + 1 Hours\n");
}
struct Transition decHours() {
    printf("xx - 1 Hours\n");
}
struct Transition incMinutes() {
    printf("xx + 1 Minutes\n");
}
struct Transition decMinutes() {
    printf("xx - 1 Minutes\n");
}
struct Transition incMonths() {
    printf("xx + 1 Months\n");
}
struct Transition decMonths() {
    printf("xx - 1 Months\n");
}
struct Transition incDays() {
    printf("xx + 1 Days\n");
}
struct Transition decDays() {
    printf("xx - 1 Days\n");
}

struct Transition displayMonthsDays();
struct Transition displayHoursMinutes();
struct Transition displayHoursAdjust();
struct Transition displayMinutesAdjust();
struct Transition displayMonthsAdjust();
struct Transition displayDaysAdjust();
struct Transition incHours();
struct Transition decHours();
struct Transition incMinutes();
struct Transition decMinutes();
struct Transition incMonths();
struct Transition decMonths();
struct Transition incDays();
struct Transition decDays();

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
    printf("--------------------Another Thread ---------------------- \n");
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