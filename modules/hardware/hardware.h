#ifndef __HARDWARE_H__
#define __HARDWARE_H__
#include <stdbool.h>
#include "libraries/Crystalfontz128x128_ST7735.h"
#include "libraries/HAL_MSP_EXP432P401R_Crystalfontz128x128_ST7735.h"

typedef enum {TIMER0,TIMER1,TIMER2,TIMER3,UNDEFINED} timerNumber;
typedef enum {DELAY,RATE,PWM,NOT_USED} timerType;

typedef struct Timers {
    void (*timer0_handler)(void);
    void (*timer1_handler)(void);
    void (*timer2_handler)(void);
    void (*timer3_handler)(void);
    timerType timer0_type;
    timerType timer1_type;
    timerType timer2_type;
    timerType timer3_type;
} Timers;

void initHardware();
void initTimerSystem();
void initClockSystem();

timerNumber generate_delay(const uint16_t delay, void* handler);

timerNumber generate_rate(const uint16_t delay, void* handler);

timerNumber generate_pwm(const uint16_t frequency, const uint8_t port, const uint8_t pin);

bool disable_timer(timerNumber timer);



Timers timerlist;
#endif
