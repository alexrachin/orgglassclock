#include <cstddef>

#ifndef FSM_UTILS
#define FSM_UTILS

enum Mode {
    HoursMinutes, MonthsDays, HoursAdjust, MinutesAdjust, MonthsAdjust, DaysAdjust
};

enum Act {
    PerTime, ModeButtonSignal, UpButtonSignal, DownButtonSignal
};

//typedef transition (*transition_callback)();

struct Transition {
    enum Mode mode;
    Transition (*transition_callback)();
};

Transition displayMonthsDays();
Transition displayHoursMinutes();
Transition displayHoursAdjust();
Transition displayMinutesAdjust();
Transition displayMonthsAdjust();
Transition displayDaysAdjust();
Transition incHours();
Transition decHours();
Transition incMinutes();
Transition decMinutes();
Transition incMonths();
Transition decMonths();
Transition incDays();
Transition decDays();

struct Transition FSM_table[6][4] = {
        {{MonthsDays, displayMonthsDays},{MonthsDays, displayMonthsDays},{HoursMinutes, NULL},{HoursMinutes, NULL}},
        {{HoursMinutes, displayHoursMinutes},{HoursAdjust, displayHoursAdjust},{MonthsDays, NULL},{MonthsDays, NULL}},
        {{HoursMinutes, displayHoursMinutes},{MinutesAdjust, displayMinutesAdjust},{HoursAdjust, incHours},{HoursAdjust, decHours}},
        {{HoursMinutes, displayHoursMinutes},{MonthsAdjust, displayMonthsAdjust},{MinutesAdjust, incMinutes},{MinutesAdjust, decMinutes}},
        {{HoursMinutes, displayHoursMinutes},{DaysAdjust, displayDaysAdjust},{MonthsAdjust, incMonths},{MonthsAdjust, decMonths}},
        {{HoursMinutes, displayHoursMinutes},{HoursMinutes, displayHoursMinutes},{DaysAdjust, incDays},{DaysAdjust, decDays}}
};

void FSMwork(Act s);

#endif