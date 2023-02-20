#include "hardware.h"

void initHardware() {
    initClockSystem();
    initTimerSystem();

}

void initTimearSystem() {
    timerlist.timer0_used=false;
    timerlist.timer1_used=false;
    timerlist.timer2_used=false;
    timerlist.timer3_used=false;
}

void initClockSystem() {
    CS_setReferenceOscillatorFrequency(CS_REFO_128KHZ);
    CS_initClockSignal(CS_ACLK, CS_REFOCLK_SELECT, CS_CLOCK_DIVIDER_1);
}
