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

    /* Initializing the clock source as follows:
         *      MCLK = MODOSC/4 = 6MHz
         *      ACLK = REFO/2 = 16kHz
         *      HSMCLK = DCO/2 = 1.5Mhz
         *      SMCLK = DCO/4 = 750kHz
         *      BCLK  = REFO = 32kHz
         */
   CS_setDCOCenteredFrequency(CS_DCO_FREQUENCY_48);
   MAP_CS_initClockSignal(CS_MCLK, CS_MODOSC_SELECT, CS_CLOCK_DIVIDER_1);
   MAP_CS_initClockSignal(CS_HSMCLK, CS_DCOCLK_SELECT, CS_CLOCK_DIVIDER_2);
   MAP_CS_initClockSignal(CS_SMCLK, CS_DCOCLK_SELECT, CS_CLOCK_DIVIDER_4);
   MAP_CS_initClockSignal(CS_BCLK, CS_REFOCLK_SELECT, CS_CLOCK_DIVIDER_1);
}

//BUTTONS
void initButtonSystem() {
    /* button S1 [P3.5]
     * button JB [P4.1]
     * specification:
     * - interrupt falling edge
     * - already has the pull-up resistor
     */
    button1Pressed = 0; //reset the button1 status flag
    GPIO_setAsInputPinWithPullUpResistor(BUT_S1_PORT, BUT_S1_PIN);
    GPIO_enableInterrupt(BUT_S1_PORT, BUT_S1_PIN);
    Interrupt_enableInterrupt(BUT_S1_PORT_INT);
    joyButtonPressed = 0;
    GPIO_setAsInputPinWithPullUpResistor(JOY_B_PORT, JOY_B_PIN);
    GPIO_enableInterrupt(JOY_B_PORT, JOY_B_PIN);
    Interrupt_enableInterrupt(JOY_B_PORT_INT);
}

// LEDS
void initLedSystem() {
    // Blue of RGB LED [P5.6]
    GPIO_setAsOutputPin(RGB_LED_BLUE_PORT, RGB_LED_BLUE_PIN);
    GPIO_setOutputLowOnPin(RGB_LED_BLUE_PORT, RGB_LED_BLUE_PIN);
}

// DIPLAY
void intiDisplaySystem(Graphics_Context* gc) {

    // Initializes display
    Crystalfontz128x128_Init();

    // Set default screen orientation
    Crystalfontz128x128_SetOrientation(LCD_ORIENTATION_UP);

    // Initializes graphics context
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

    // Initializing ADC (MCLK/1/4)
    ADC14_initModule(ADC_CLOCKSOURCE_MCLK, ADC_PREDIVIDER_1, ADC_DIVIDER_1, 0);

    // Configuring ADC Memory and ADC mode  !![add here for new adc pin]!!
    ADC14_configureMultiSequenceMode(JOY_Y_MEM, JOY_X_MEM, 0);
    // joy_x
    ADC14_configureConversionMemory(JOY_X_MEM, ADC_VREFPOS_AVCC_VREFNEG_VSS, JOY_X_ADC_CH, false);
    // joy_y
    ADC14_configureConversionMemory(JOY_Y_MEM, ADC_VREFPOS_AVCC_VREFNEG_VSS, JOY_Y_ADC_CH, false);

    // Configuring Sample Timer
    ADC14_enableSampleTimer(ADC_MANUAL_ITERATION);

    // set resolution at 8-bits (we don't need more for the joystick)
    ADC14_setResolution(ADC_8BIT);

    // Enabling Conversion
    ADC14_enableConversion();


}

/* start up time */
 const RTC_C_Calendar currentTime = {
         0x32,
         0x01,
         0x15,
         0x06,
         0x12,
         0x11,
         0x2023
 };

void initRTCSystem() {
    /* Initializing RTC with current time as described in time in
     * definitions section */
    MAP_RTC_C_initCalendar(&currentTime, RTC_C_FORMAT_BINARY);

    /* Specify an interrupt to assert every minute */
    MAP_RTC_C_setCalendarEvent(RTC_C_CALENDAREVENT_MINUTECHANGE);

    /* Enable interrupt for RTC Ready Status, which asserts when the RTC
     * Calendar registers are ready to read. */
    MAP_RTC_C_clearInterruptFlag(RTC_C_CLOCK_READ_READY_INTERRUPT | RTC_C_TIME_EVENT_INTERRUPT | RTC_C_CLOCK_ALARM_INTERRUPT);
    MAP_RTC_C_enableInterrupt(RTC_C_CLOCK_READ_READY_INTERRUPT | RTC_C_TIME_EVENT_INTERRUPT | RTC_C_CLOCK_ALARM_INTERRUPT);

    /* Start RTC Clock */
    MAP_RTC_C_startClock();

}

/* TIMER FUNCTIONS */
timerNumber generate_delay(const uint16_t delay, void* handler) {
    timerNumber selectedTimer=NONE;
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
    timerNumber selectedTimer=NONE;
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
    timerNumber selectedTimer=NONE;
        if (volume <= 100 && frequency<=64000  && !(timerlist.timer0_type==PWM || timerlist.timer1_type==PWM || timerlist.timer2_type==PWM || timerlist.timer3_type==PWM)) {
            uint16_t timerValue=(1/frequency)*64000;
            uint16_t timerDutyCycle= volume*65536/100;
            GPIO_setAsPeripheralModuleFunctionInputPin(port, pin, GPIO_PRIMARY_MODULE_FUNCTION);
            Timer_A_PWMConfig config;
            config.clockSource=TIMER_A_CLOCKSOURCE_ACLK;
            config.clockSourceDivider=TIMER_A_CLOCKSOURCE_DIVIDER_2;
            config.compareRegister=TIMER_A_CAPTURECOMPARE_REGISTER_1;
            config.dutyCycle=timerDutyCycle;
            config.timerPeriod=timerValue;
            config.compareOutputMode=TIMER_A_OUTPUTMODE_TOGGLE;

            if (timerlist.timer0_type==NOT_USED) {
                timerlist.timer0_type=PWM;
                selectedTimer=TIMER0;
                Timer_A_generatePWM(TIMER_A0_BASE,&config);
                return selectedTimer;
            }
            if (timerlist.timer1_type==NOT_USED) {
                timerlist.timer1_type=PWM;
                selectedTimer=TIMER1;
                Timer_A_generatePWM(TIMER_A1_BASE,&config);
                return selectedTimer;
            }
            if (timerlist.timer2_type==NOT_USED) {
                timerlist.timer2_type=PWM;
                selectedTimer=TIMER2;
                Timer_A_generatePWM(TIMER_A2_BASE,&config);
                return selectedTimer;
            }
            if (timerlist.timer3_type==NOT_USED) {
                timerlist.timer3_type=PWM;
                selectedTimer=TIMER3;
                Timer_A_generatePWM(TIMER_A3_BASE,&config);
                return selectedTimer;
            }
        }
        return selectedTimer;
}

void disable_timer(timerNumber timer) {
    switch(timer) {
    case TIMER0:
        Timer_A_stopTimer(TIMER_A0_BASE);
        Interrupt_disableInterrupt(INT_TA0_0);
        timerlist.timer0_type=NOT_USED;
        break;
    case TIMER1:
        Timer_A_stopTimer(TIMER_A1_BASE);
        Interrupt_disableInterrupt(INT_TA1_0);
        timerlist.timer1_type=NOT_USED;
        break;
    case TIMER2:
        Timer_A_stopTimer(TIMER_A2_BASE);
        Interrupt_disableInterrupt(INT_TA2_0);
        timerlist.timer2_type=NOT_USED;
        break;
    case TIMER3:
        Timer_A_stopTimer(TIMER_A3_BASE);
        Interrupt_disableInterrupt(INT_TA3_0);
        timerlist.timer3_type=NOT_USED;
        break;
    }
}

/* TIMERS IRQ */
void TA0_0_IRQHandler(void)
{
    Timer_A_clearCaptureCompareInterrupt(TIMER_A0_BASE,TIMER_A_CAPTURECOMPARE_REGISTER_0);
    switch(timerlist.timer0_type) {
        case DELAY:
            Timer_A_stopTimer(TIMER_A0_BASE);
            Interrupt_disableInterrupt(INT_TA0_0);
            timerlist.timer0_type=NOT_USED;
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
            timerlist.timer1_type=NOT_USED;
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
            timerlist.timer2_type=NOT_USED;
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
            timerlist.timer3_type=NOT_USED;
        case RATE:
            timerlist.timer3_handler();
            break;
        case PWM:
            break;
        }
}

/* BUTTONS FUNCTIONS */
uint8_t Button1Pressed() {

}


/* BUTTONS IRQ */
// PORT4 IRQ
void PORT4_IRQHandler(void) {
    uint_fast16_t status = GPIO_getEnabledInterruptStatus(GPIO_PORT_P4); // check which pins generated the interrupt
        GPIO_clearInterruptFlag(GPIO_PORT_P4, status); // clear the interrupt flag (to clear pending interrupt indicator)
        joyButtonPressed = 1;
}
// PORT5 IRQ
void PORT5_IRQHandler(void) {
    uint_fast16_t status = GPIO_getEnabledInterruptStatus(GPIO_PORT_P5); // check which pins generated the interrupt
    GPIO_clearInterruptFlag(GPIO_PORT_P5, status); // clear the interrupt flag (to clear pending interrupt indicator)
    button1Pressed = 1;
}

/* ADC FUNCTIONS */
joystick getJoyValue() {
    joystick JoyValues;
    ADC14_toggleConversionTrigger();
    JoyValues.joyXvalue = ADC14_getResult(JOY_X_MEM);    // read the adc value
    JoyValues.joyYvalue = ADC14_getResult(JOY_Y_MEM);    // read the adc value
    return JoyValues;
}

/* RTC FUNCTIONS */
// RTC IRQ is in clock.c file



