#ifndef __HARDWARE_H__
#define __HARDWARE_H__
#include <stdbool.h>
#include "libraries/Crystalfontz128x128_ST7735.h"
#include "libraries/HAL_MSP_EXP432P401R_Crystalfontz128x128_ST7735.h"

typedef struct Timers {
    bool timer0_used;
    bool timer1_used;
    bool timer2_used;
    bool timer3_used;
} Timers;

void initHardware();
void initTimerSystem();
void initClockSystem();
Timers timerlist;
#endif
