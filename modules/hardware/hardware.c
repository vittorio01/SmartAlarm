#include "hardware.h"

void initHardware() {
    initClockSystem();
    initTimerSystem();

}

void initTimerSystem() {

    timerlist.timer0_type=NOT_USED;
    timerlist.timer1_type=NOT_USED;
    timerlist.timer2_type=NOT_USED;
    timerlist.timer3_type=NOT_USED;
}

void initClockSystem() {
    CS_setReferenceOscillatorFrequency(CS_REFO_128KHZ);
    CS_initClockSignal(CS_ACLK, CS_REFOCLK_SELECT, CS_CLOCK_DIVIDER_1);
}

timerNumber generate_delay(const uint16_t delay, void* handler) {
    timerNumber selectedTimer=UNDEFINED;
    if (delay<=32768) {
        Timer_A_UpModeConfig config;
        config.clockSource=TIMER_A_CLOCKSOURCE_ACLK;
        config.clockSourceDivider=TIMER_A_CLOCKSOURCE_DIVIDER_64;
        config.timerInterruptEnable_TAIE=TIMER_A_TAIE_INTERRUPT_DISABLE;
        config.captureCompareInterruptEnable_CCR0_CCIE=TIMER_A_CCIE_CCR0_INTERRUPT_ENABLE;
        config.timerClear=TIMER_A_DO_CLEAR;
        config.timerPeriod=delay*2;
        if (timerlist.timer0_type==NOT_USED) {
            timerlist.timer0_type=DELAY;
            selectedTimer=TIMER0;
            Timer_A_configureUpMode(TIMER_A0_BASE,&config);
            Timer_A_startCounter(TIMER_A0_BASE,TIMER_A_UP_MODE);
            Interrupt_enableInterrupt(INT_TA0_0);
            return selectedTimer;
        }
        if (timerlist.timer1_type==NOT_USED) {
            timerlist.timer1_type=DELAY;
            selectedTimer=TIMER1;
            Timer_A_configureUpMode(TIMER_A1_BASE,&config);
            Timer_A_startCounter(TIMER_A1_BASE,TIMER_A_UP_MODE);
            Interrupt_enableInterrupt(INT_TA1_0);
            return selectedTimer;
        }
        if (timerlist.timer2_type==NOT_USED) {
            timerlist.timer2_type=DELAY;
            selectedTimer=TIMER2;
            Timer_A_configureUpMode(TIMER_A2_BASE,&config);
            Timer_A_startCounter(TIMER_A2_BASE,TIMER_A_UP_MODE);
            Interrupt_enableInterrupt(INT_TA2_0);
            return selectedTimer;
        }
        if (timerlist.timer3_type==NOT_USED) {
            timerlist.timer3_type=DELAY;
            selectedTimer=TIMER3;
            Timer_A_configureUpMode(TIMER_A3_BASE,&config);
            Timer_A_startCounter(TIMER_A3_BASE,TIMER_A_UP_MODE);
            Interrupt_enableInterrupt(INT_TA3_0);
            return selectedTimer;
        }
    }
    return selectedTimer;
}

timerNumber generate_rate(const uint16_t delay, void* handler) {
    timerNumber selectedTimer=UNDEFINED;
        if (delay<=32768) {
            Timer_A_UpModeConfig config;
            config.clockSource=TIMER_A_CLOCKSOURCE_ACLK;
            config.clockSourceDivider=TIMER_A_CLOCKSOURCE_DIVIDER_64;
            config.timerInterruptEnable_TAIE=TIMER_A_TAIE_INTERRUPT_DISABLE;
            config.captureCompareInterruptEnable_CCR0_CCIE=TIMER_A_CCIE_CCR0_INTERRUPT_ENABLE;
            config.timerClear=TIMER_A_DO_CLEAR;
            config.timerPeriod=delay*2;
            if (timerlist.timer0_type==NOT_USED) {
                timerlist.timer0_type=RATE;
                selectedTimer=TIMER0;
                Timer_A_configureUpMode(TIMER_A0_BASE,&config);
                Timer_A_startCounter(TIMER_A0_BASE,TIMER_A_UP_MODE);
                Interrupt_enableInterrupt(INT_TA0_0);
                return selectedTimer;
            }
            if (timerlist.timer1_type==NOT_USED) {
                timerlist.timer1_type=RATE;
                selectedTimer=TIMER1;
                Timer_A_configureUpMode(TIMER_A1_BASE,&config);
                Timer_A_startCounter(TIMER_A1_BASE,TIMER_A_UP_MODE);
                Interrupt_enableInterrupt(INT_TA1_0);
                return selectedTimer;
            }
            if (timerlist.timer2_type==NOT_USED) {
                timerlist.timer2_type=RATE;
                selectedTimer=TIMER2;
                Timer_A_configureUpMode(TIMER_A2_BASE,&config);
                Timer_A_startCounter(TIMER_A2_BASE,TIMER_A_UP_MODE);
                Interrupt_enableInterrupt(INT_TA2_0);
                return selectedTimer;
            }
            if (timerlist.timer3_type==NOT_USED) {
                timerlist.timer3_type=RATE;
                selectedTimer=TIMER3;
                Timer_A_configureUpMode(TIMER_A3_BASE,&config);
                Timer_A_startCounter(TIMER_A3_BASE,TIMER_A_UP_MODE);
                Interrupt_enableInterrupt(INT_TA3_0);
                return selectedTimer;
            }
        }
        return selectedTimer;
}

timerNumber generate_pwm(const uint16_t frequency, const uint16_t volume, const uint8_t port, const uint8_t pin) {
    timerNumber selectedTimer=UNDEFINED;
        if (delay<=32768) {
            Timer_A_UpModeConfig config;
            config.clockSource=TIMER_A_CLOCKSOURCE_ACLK;
            config.clockSourceDivider=TIMER_A_CLOCKSOURCE_DIVIDER_2;
            config.timerInterruptEnable_TAIE=TIMER_A_TAIE_INTERRUPT_DISABLE;
            config.captureCompareInterruptEnable_CCR0_CCIE=TIMER_A_CCIE_CCR0_INTERRUPT_DISABLE;
            config.timerClear=TIMER_A_DO_CLEAR;
            config.timerPeriod=frequency;

            Timer_A_CompareModeConfig compareConfig;
            compareConfig.compareInterruptEnable=TIMER_A_CAPTURECOMPARE_INTERRUPT_DISABLE;
            compareConfig.compareOutputMode=TIMER_A_OUTPUTMODE_TOGGLE_SET;
            compareConfig.compareValue=volume
            compareConfig.compareRegister=1;

              piezo.upConfig_PWM.captureCompareInterruptEnable_CCR0_CCIE = TIMER_A_TAIE_INTERRUPT_DISABLE;
              piezo.upConfig_PWM.clockSource=TIMER_A_CLOCKSOURCE_SMCLK;
              piezo.upConfig_PWM.clockSourceDivider=TIMER_A_CLOCKSOURCE_DIVIDER_4;
              piezo.upConfig_PWM.timerClear=TIMER_A_DO_CLEAR;
              piezo.upConfig_PWM.timerInterruptEnable_TAIE=TIMER_A_TAIE_INTERRUPT_DISABLE;
              piezo.upConfig_PWM.timerPeriod=0;
            if (timerlist.timer0_type==NOT_USED) {
                timerlist.timer0_type=PWM;
                selectedTimer=TIMER0;
                Timer_A_configureUpMode(TIMER_A0_BASE,&config);
                Timer_A_startCounter(TIMER_A0_BASE,TIMER_A_UP_MODE);
                Interrupt_enableInterrupt(INT_TA0_0);
                return selectedTimer;
            }
            if (timerlist.timer1_type==NOT_USED) {
                timerlist.timer1_type=PWM;
                selectedTimer=TIMER1;
                Timer_A_configureUpMode(TIMER_A1_BASE,&config);
                Timer_A_startCounter(TIMER_A1_BASE,TIMER_A_UP_MODE);
                Interrupt_enableInterrupt(INT_TA1_0);
                return selectedTimer;
            }
            if (timerlist.timer2_type==NOT_USED) {
                timerlist.timer2_type=PWM;
                selectedTimer=TIMER2;
                Timer_A_configureUpMode(TIMER_A2_BASE,&config);
                Timer_A_startCounter(TIMER_A2_BASE,TIMER_A_UP_MODE);
                Interrupt_enableInterrupt(INT_TA2_0);
                return selectedTimer;
            }
            if (timerlist.timer3_type==NOT_USED) {
                timerlist.timer3_type=PWM;
                selectedTimer=TIMER3;
                Timer_A_configureUpMode(TIMER_A3_BASE,&config);
                Timer_A_startCounter(TIMER_A3_BASE,TIMER_A_UP_MODE);
                Interrupt_enableInterrupt(INT_TA3_0);
                return selectedTimer;
            }
        }
        return selectedTimer;
}

bool disable_timer(timerNumber timer) {
    if (timer==TIMER0) {
            Timer_A_stopTimer(TIMER_A0_BASE);
            Interrupt_disableInterrupt(INT_TA0_0);
            timerlist.timer2_type=NOT_USED;
            return true;
    }
    if (timer==TIMER1) {
            Timer_A_stopTimer(TIMER_A1_BASE);
            Interrupt_disableInterrupt(INT_TA1_0);
            timerlist.timer2_type=NOT_USED;
            return true;
    }
    if (timer==TIMER2) {
            Timer_A_stopTimer(TIMER_A2_BASE);
            Interrupt_disableInterrupt(INT_TA2_0);
            timerlist.timer2_type=NOT_USED;
            return true;
    }
    if (timer==TIMER3) {
            Timer_A_stopTimer(TIMER_A3_BASE);
            Interrupt_disableInterrupt(INT_TA3_0);
            timerlist.timer2_type=NOT_USED;
            return true;
    }
    return false;
}

void TA0_0_IRQHandler(void)
{
    Timer_A_clearCaptureCompareInterrupt(TIMER_A0_BASE,TIMER_A_CAPTURECOMPARE_REGISTER_0);
    switch(timerlist.timer0_type) {
        case DELAY:
            Timer_A_stopTimer(TIMER_A0_BASE);
            Interrupt_disableInterrupt(INT_TA0_0);
        case RATE:
            timerlist.timer0_handler();
            break;
        case PWM:
            break;
        }

}

void TA1_0_IRQHandler(void)
{
    Timer_A_clearCaptureCompareInterrupt(TIMER_A1_BASE,TIMER_A_CAPTURECOMPARE_REGISTER_0);
    switch(timerlist.timer1_type) {
        case DELAY:
            Timer_A_stopTimer(TIMER_A1_BASE);
            Interrupt_disableInterrupt(INT_TA1_0);
        case RATE:
            timerlist.timer1_handler();
            break;
        case PWM:
            break;
        }
}

void TA2_0_IRQHandler(void)
{
    switch(timerlist.timer2_type) {
        case DELAY:
            Timer_A_stopTimer(TIMER_A2_BASE);
            Interrupt_disableInterrupt(INT_TA2_0);
        case RATE:
            timerlist.timer2_handler();
            break;
        case PWM:
            break;
        }
}

void TA3_0_IRQHandler(void)
{
    Timer_A_clearCaptureCompareInterrupt(TIMER_A3_BASE,TIMER_A_CAPTURECOMPARE_REGISTER_0);
    switch(timerlist.timer3_type) {
        case DELAY:
            Timer_A_stopTimer(TIMER_A3_BASE);
            Interrupt_disableInterrupt(INT_TA3_0);
        case RATE:
            timerlist.timer3_handler();
            break;
        case PWM:
            break;
        }
}
