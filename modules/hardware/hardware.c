#include "hardware.h"

void initHardware() {
    initTimerSystem();

}

void initTimerSystem() {
    timerlist.timer0_used=false;
    timerlist.timer1_used=false;
    timerlist.timer2_used=false;
    timerlist.timer3_used=false;
}
