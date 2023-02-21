#include "hardware.h"

/* GENERALS INIT. */
void initHardware(Graphics_Context* gc) {
    initClockSystem();
    initTimerSystem();
    initButtonSystem();
    initLedSystem();
    intiDisplaySystem(gc);
    initAdcSystem();
}

/* MODULES INIT. */

// TIMERS
void initTimerSystem() {

    timerlist.timer0_type=NOT_USED;
    timerlist.timer1_type=NOT_USED;
    timerlist.timer2_type=NOT_USED;
    timerlist.timer3_type=NOT_USED;
}

// CLOCK SYSTEM
void initClockSystem() {
    CS_setReferenceOscillatorFrequency(CS_REFO_128KHZ);
    CS_initClockSignal(CS_ACLK, CS_REFOCLK_SELECT, CS_CLOCK_DIVIDER_1);
}

//BUTTONS
void initButtonSystem() {
    /* button S1 [P3.5]
     * specification:
     * - interrupt falling edge
     * - already has the pull-up resistor
     */
    GPIO_setAsInputPinWithPullUpResistor(BUT_S1_PORT, BUT_S1_PIN);
    GPIO_enableInterrupt(BUT_S1_PORT, BUT_S1_PIN);
    Interrupt_enableInterrupt(BUT_S1_PORT_INT);
}

// LEDS
void initLedSystem() {
    /* Blue of RGB LED [P5.6]
     *
     */
    GPIO_setAsOutputPin(RGB_LED_BLUE_PORT, RGB_LED_BLUE_PIN);
    GPIO_setOutputLowOnPin(RGB_LED_BLUE_PORT, RGB_LED_BLUE_PIN);
}

// DIPLAY
void intiDisplaySystem(Graphics_Context* gc) {
    /* Initializes display */
    Crystalfontz128x128_Init();

    /* Set default screen orientation */
    Crystalfontz128x128_SetOrientation(LCD_ORIENTATION_UP);

    /* Initializes graphics context */
    Graphics_initContext(gc, &g_sCrystalfontz128x128,&g_sCrystalfontz128x128_funcs);
    Graphics_setForegroundColor(gc, GRAPHICS_COLOR_RED);
    Graphics_setBackgroundColor(gc, GRAPHICS_COLOR_WHITE);
    GrContextFontSet(gc, &g_sFontFixed6x8);
    Graphics_clearDisplay(gc);
}

// ADC14
void initAdcSystem() {
    // Configuring GPIOs  !![add here for new adc pin]!!
    GPIO_setAsPeripheralModuleFunctionInputPin(JOY_X_PORT, JOY_X_PIN, GPIO_TERTIARY_MODULE_FUNCTION);
    GPIO_setAsPeripheralModuleFunctionInputPin(JOY_Y_PORT, JOY_Y_PIN, GPIO_TERTIARY_MODULE_FUNCTION);

    ADC14_enableModule();   // enable ADC block

    //![Single Sample Mode Configure]
    /* Initializing ADC (MCLK/1/4) */
    ADC14_initModule(ADC_CLOCKSOURCE_MCLK, ADC_PREDIVIDER_1, ADC_DIVIDER_4, 0);

    // Configuring ADC Memory !![add here for new adc pin]!!
    // joy_x
    ADC14_configureSingleSampleMode(JOY_X_MEM, true);
    ADC14_configureConversionMemory(JOY_X_MEM, ADC_VREFPOS_AVCC_VREFNEG_VSS, JOY_X_ADC_CH, false);
    // joy_y
    ADC14_configureSingleSampleMode(JOY_Y_MEM, true);
    ADC14_configureConversionMemory(JOY_Y_MEM, ADC_VREFPOS_AVCC_VREFNEG_VSS, JOY_Y_ADC_CH, false);

    /* Configuring Sample Timer */
    ADC14_enableSampleTimer(ADC_MANUAL_ITERATION);

    /* Enabling/Toggling Conversion */
    ADC14_enableConversion();
    ADC14_toggleConversionTrigger();
    //![Single Sample Mode Configure]

    // set resolution at 8-bits (we don't need more for the joystick)
    ADC14_setResolution(ADC_8BIT);

    /* Enabling interrupts */
    Interrupt_enableInterrupt(INT_ADC14);
}

/* TIMER FUNCTIONS */
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
            compareConfig.compareValue=volume;
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

/* TIMERS IRQ */
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

/* BUTTONS FUNCTIONS */

/* BUTTONS IRQ */
// PORT5 INTERRUPT ISR
void PORT5_IRQHandler(void) {
    uint_fast16_t status = GPIO_getEnabledInterruptStatus(GPIO_PORT_P5); //check which pins generated the interrupt
    GPIO_clearInterruptFlag(GPIO_PORT_P5, status); //clear the interrupt flag (to clear pending interrupt indicator)

    if (status & BUT_S1_PIN) { //check if the button S1 was pressed
        switch (current_activity) {
        case CLOCK: break;
        case GAME: break;
        }
    }
}

/* ADC FUNCTIONS */
void enableJoyInterrupt() { //enable the joystick adc interrupt
    ADC14_enableInterrupt(JOY_X_INT);
}
void disableJoyInterrupt() { //disable the joystick adc interrupt
    ADC14_disableInterrupt(JOY_X_INT);
}

/* ADC14 IRQ */
void ADC14_IRQHandler() {
    uint64_t status = ADC14_getEnabledInterruptStatus();  //same as the gpio int
    ADC14_clearInterruptFlag(status);                     //same as the gpio int
    if (JOY_X_INT & status) {
        adcJoy.joyXvalue = ADC14_getResult(JOY_X_MEM);    //read the adc value
        adcJoy.joyYvalue = ADC14_getResult(JOY_Y_MEM);    //read the adc value
    }
    ADC14_toggleConversionTrigger();    //start a new conversion
}

