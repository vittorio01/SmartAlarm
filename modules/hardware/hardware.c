#include "hardware.h"

/* GENERALS INIT. */
void initHardware(Graphics_Context* gc) {
    Interrupt_enableMaster();
    initPCM();
    initClockSystem();
    initTimerSystem();
    initButtonSystem();
    initLedSystem();
    intiDisplaySystem(gc);
    initAdcSystem();
    initRTCSystem();
}

/* MODULES INIT. */

void initPCM() {
    PCM_setCoreVoltageLevel(PCM_VCORE1);
    FlashCtl_setWaitState(FLASH_BANK0, 2);
    FlashCtl_setWaitState(FLASH_BANK1, 2);
}

// TIMERS
void initTimerSystem() {

    timerlist.timer0_type=NOT_USED;
    timerlist.timer1_type=NOT_USED;
    timerlist.timer2_type=NOT_USED;
    timerlist.timer3_type=NOT_USED;
}

// CLOCK SYSTEM
void initClockSystem() {
    /*
    CS_setReferenceOscillatorFrequency(CS_REFO_128KHZ);
    CS_initClockSignal(CS_ACLK, CS_REFOCLK_SELECT, CS_CLOCK_DIVIDER_1);*/

    /* Initializing the clock source as follows:
         *      MCLK = MODOSC/4 = 6MHz
         *      ACLK = REFO/2 = 16kHz
         *      HSMCLK = DCO/2 = 1.5Mhz
         *      SMCLK = DCO/4 = 750kHz
         *      BCLK  = REFO = 32kHz
         */
   CS_setDCOCenteredFrequency(CS_DCO_FREQUENCY_48);
   CS_initClockSignal(CS_MCLK, CS_MODOSC_SELECT, CS_CLOCK_DIVIDER_1);
   CS_initClockSignal(CS_HSMCLK, CS_DCOCLK_SELECT, CS_CLOCK_DIVIDER_2);
   CS_initClockSignal(CS_SMCLK, CS_DCOCLK_SELECT, CS_CLOCK_DIVIDER_4);
   CS_initClockSignal(CS_BCLK, CS_REFOCLK_SELECT, CS_CLOCK_DIVIDER_1);
}

//BUTTONS
void initButtonSystem() {
    /* button S1 [P3.5]
     * button JB [P4.1]
     * specification:
     * - interrupt falling edge
     * - already has the pull-up resistor
     */

    GPIO_setAsInputPinWithPullUpResistor(BUT_S1_PORT, BUT_S1_PIN);
    GPIO_enableInterrupt(BUT_S1_PORT, BUT_S1_PIN);
    Interrupt_enableInterrupt(BUT_S1_PORT_INT);

    GPIO_setAsInputPinWithPullUpResistor(BUT_S2_PORT, BUT_S2_PIN);
    GPIO_enableInterrupt(BUT_S2_PORT, BUT_S2_PIN);
    Interrupt_enableInterrupt(BUT_S2_PORT_INT);

    GPIO_setAsInputPinWithPullUpResistor(JOY_B_PORT, JOY_B_PIN);
    GPIO_enableInterrupt(JOY_B_PORT, JOY_B_PIN);
    Interrupt_enableInterrupt(JOY_B_PORT_INT);

    buttonsPressed.b1 = 0; //reset the button1 status flag
    buttonsPressed.b2 = 0;
    buttonsPressed.jb = 0;
}

// LEDS
void initLedSystem() {
    GPIO_setAsOutputPin(RGB_LED_BLUE_PORT, RGB_LED_BLUE_PIN);
    GPIO_setOutputLowOnPin(RGB_LED_BLUE_PORT, RGB_LED_BLUE_PIN);

    GPIO_setAsOutputPin(RGB_LED_RED_PORT, RGB_LED_RED_PIN);
    GPIO_setOutputLowOnPin(RGB_LED_RED_PORT, RGB_LED_RED_PIN);

    GPIO_setAsOutputPin(RGB_LED_GREEN_PORT, RGB_LED_GREEN_PIN);
    GPIO_setOutputLowOnPin(RGB_LED_GREEN_PORT, RGB_LED_GREEN_PIN);
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
    ADC14_initModule(ADC_CLOCKSOURCE_MCLK, ADC_PREDIVIDER_4, ADC_DIVIDER_4, 0);

    // Configuring ADC Memory and ADC mode  !![add here for new adc pin]!!
    ADC14_configureMultiSequenceMode(JOY_Y_MEM, JOY_X_MEM, 0);
    ADC14_configureConversionMemory(JOY_X_MEM, ADC_VREFPOS_AVCC_VREFNEG_VSS, JOY_X_ADC_CH, false);
    ADC14_configureConversionMemory(JOY_Y_MEM, ADC_VREFPOS_AVCC_VREFNEG_VSS, JOY_Y_ADC_CH, false);

    // Configuring Sample Timer
    ADC14_enableSampleTimer(ADC_AUTOMATIC_ITERATION);

    // set resolution at 8-bits (we don't need more for the joystick)
    ADC14_setResolution(ADC_8BIT);

    // Enabling Conversion
    ADC14_enableInterrupt(JOY_X_MEM);
    Interrupt_enableInterrupt(INT_ADC14);



}

/* start up time */
 const RTC_C_Calendar currentTime = {
         0x32,
         0x59,
         0x23,
         0x06,
         0x12,
         0x11,
         0x2023
 };

void initRTCSystem() {
    /* Initializing RTC with current time as described in time in
     * definitions section */
    RTC_C_initCalendar(&currentTime, RTC_C_FORMAT_BCD);

    /* Specify an interrupt to assert every minute */
    RTC_C_setCalendarEvent(RTC_C_CALENDAREVENT_MINUTECHANGE);

    /* Enable interrupt for RTC Ready Status, which asserts when the RTC
     * Calendar registers are ready to read. */
    RTC_C_clearInterruptFlag(RTC_C_CLOCK_READ_READY_INTERRUPT | RTC_C_TIME_EVENT_INTERRUPT | RTC_C_CLOCK_ALARM_INTERRUPT);
    RTC_C_enableInterrupt(RTC_C_CLOCK_READ_READY_INTERRUPT | RTC_C_TIME_EVENT_INTERRUPT | RTC_C_CLOCK_ALARM_INTERRUPT);

    /* Start RTC Clock & enable Interrupts*/
    RTC_C_startClock();
    Interrupt_enableInterrupt(INT_RTC_C);
    Interrupt_enableMaster();

}

/* TIMER FUNCTIONS */
timerNumber generate_delay(const uint16_t delay, void* handler) {
    timerNumber selectedTimer=NONE;
    if (delay<=32768 && delay!=0) {

        Timer_A_UpModeConfig config;
        config.clockSource=TIMER_A_CLOCKSOURCE_ACLK;
        config.clockSourceDivider=TIMER_A_CLOCKSOURCE_DIVIDER_16;
        config.timerInterruptEnable_TAIE=TIMER_A_TAIE_INTERRUPT_DISABLE;
        config.captureCompareInterruptEnable_CCR0_CCIE=TIMER_A_CCIE_CCR0_INTERRUPT_ENABLE;
        config.timerClear=TIMER_A_DO_CLEAR;
        config.timerPeriod=delay*2;
        if (timerlist.timer1_type==NOT_USED) {
            timerlist.timer1_type=DELAY;
            selectedTimer=TIMER1;
            Timer_A_configureUpMode(TIMER_A1_BASE,&config);
            timerlist.timer1_handler=handler;
            Timer_A_startCounter(TIMER_A1_BASE,TIMER_A_UP_MODE);
            Interrupt_enableInterrupt(INT_TA1_0);
            return selectedTimer;
        }
        if (timerlist.timer2_type==NOT_USED) {
            timerlist.timer2_type=DELAY;
            selectedTimer=TIMER2;
            Timer_A_configureUpMode(TIMER_A2_BASE,&config);
            timerlist.timer2_handler=handler;
            Timer_A_startCounter(TIMER_A2_BASE,TIMER_A_UP_MODE);
            Interrupt_enableInterrupt(INT_TA2_0);
            return selectedTimer;
        }
        if (timerlist.timer3_type==NOT_USED) {
            timerlist.timer3_type=DELAY;
            selectedTimer=TIMER3;
            Timer_A_configureUpMode(TIMER_A3_BASE,&config);
            timerlist.timer3_handler=handler;
            Timer_A_startCounter(TIMER_A3_BASE,TIMER_A_UP_MODE);
            Interrupt_enableInterrupt(INT_TA3_0);
            return selectedTimer;
        }
    }
    return selectedTimer;
}

void generate_wait(const uint16_t delay) {
    if (delay<=32768 && delay!=0) {
        Timer_A_UpModeConfig config;
        config.clockSource=TIMER_A_CLOCKSOURCE_ACLK;
        config.clockSourceDivider=TIMER_A_CLOCKSOURCE_DIVIDER_16;
        config.timerInterruptEnable_TAIE=TIMER_A_TAIE_INTERRUPT_DISABLE;
        config.captureCompareInterruptEnable_CCR0_CCIE=TIMER_A_CCIE_CCR0_INTERRUPT_ENABLE;
        config.timerClear=TIMER_A_DO_CLEAR;
        config.timerPeriod=delay*2;
        if (timerlist.timer1_type==NOT_USED) {
            timerlist.timer1_type=WAIT;
            Timer_A_configureUpMode(TIMER_A1_BASE,&config);
            Timer_A_startCounter(TIMER_A1_BASE,TIMER_A_UP_MODE);
            Interrupt_enableInterrupt(INT_TA1_0);
            while (timerlist.timer1_type==WAIT) {
                PCM_gotoLPM0();
            }

            return;
        }
        if (timerlist.timer2_type==NOT_USED) {
            timerlist.timer2_type=WAIT;
            Timer_A_configureUpMode(TIMER_A2_BASE,&config);
            Timer_A_startCounter(TIMER_A2_BASE,TIMER_A_UP_MODE);
            Interrupt_enableInterrupt(INT_TA2_0);
            while (timerlist.timer2_type==WAIT) {
                PCM_gotoLPM0();
            }
            return;
        }
        if (timerlist.timer3_type==NOT_USED) {
            timerlist.timer3_type=WAIT;
            Timer_A_configureUpMode(TIMER_A3_BASE,&config);
            Timer_A_startCounter(TIMER_A3_BASE,TIMER_A_UP_MODE);
            Interrupt_enableInterrupt(INT_TA3_0);
            while (timerlist.timer3_type==WAIT) {
                PCM_gotoLPM0();
            }
            return;
        }
    }

}

timerNumber generate_rate(const uint16_t delay, void* handler) {
    timerNumber selectedTimer=NONE;
        if (delay<=32768 && delay!=0) {
            Timer_A_UpModeConfig config;
            config.clockSource=TIMER_A_CLOCKSOURCE_ACLK;
            config.clockSourceDivider=TIMER_A_CLOCKSOURCE_DIVIDER_16;
            config.timerInterruptEnable_TAIE=TIMER_A_TAIE_INTERRUPT_DISABLE;
            config.captureCompareInterruptEnable_CCR0_CCIE=TIMER_A_CCIE_CCR0_INTERRUPT_ENABLE;
            config.timerClear=TIMER_A_DO_CLEAR;
            config.timerPeriod=delay*2;
            if (timerlist.timer1_type==NOT_USED) {
                timerlist.timer1_type=RATE;
                selectedTimer=TIMER1;
                Timer_A_configureUpMode(TIMER_A1_BASE,&config);
                timerlist.timer1_handler=handler;
                Timer_A_startCounter(TIMER_A1_BASE,TIMER_A_UP_MODE);
                Interrupt_enableInterrupt(INT_TA1_0);
                return selectedTimer;
            }
            if (timerlist.timer2_type==NOT_USED) {
                timerlist.timer2_type=RATE;
                selectedTimer=TIMER2;
                Timer_A_configureUpMode(TIMER_A2_BASE,&config);
                timerlist.timer2_handler=handler;
                Timer_A_startCounter(TIMER_A2_BASE,TIMER_A_UP_MODE);
                Interrupt_enableInterrupt(INT_TA2_0);
                return selectedTimer;
            }
            if (timerlist.timer3_type==NOT_USED) {
                timerlist.timer3_type=RATE;
                selectedTimer=TIMER3;
                Timer_A_configureUpMode(TIMER_A3_BASE,&config);
                timerlist.timer3_handler=handler;
                Timer_A_startCounter(TIMER_A3_BASE,TIMER_A_UP_MODE);
                Interrupt_enableInterrupt(INT_TA3_0);
                return selectedTimer;
            }
        }
        return selectedTimer;
}

void generate_tone(const uint16_t frequency, const uint16_t volume) {
    if ((volume <= 100 && frequency<=250000) && (volume!=0 && frequency!=0)) {
        if (timerlist.timer0_type!=NOT_USED) disable_tone();
        uint16_t timerValue=(250000/frequency);
        uint16_t timerDutyCycle= volume*timerValue/200;
        GPIO_setAsPeripheralModuleFunctionOutputPin(BUZZER_PORT, BUZZER_PIN,GPIO_PRIMARY_MODULE_FUNCTION);

        Timer_A_CompareModeConfig compareConfig_PWM = {
                TIMER_A_CAPTURECOMPARE_REGISTER_4,
                TIMER_A_CAPTURECOMPARE_INTERRUPT_DISABLE,
                TIMER_A_OUTPUTMODE_TOGGLE_SET,
                timerDutyCycle
                };

        Timer_A_UpModeConfig upConfig = {
                TIMER_A_CLOCKSOURCE_SMCLK,
                TIMER_A_CLOCKSOURCE_DIVIDER_12,
                timerValue,
                TIMER_A_TAIE_INTERRUPT_DISABLE,
                TIMER_A_CCIE_CCR0_INTERRUPT_DISABLE,
                TIMER_A_DO_CLEAR
                };
        timerlist.timer0_type=PWM;
        Timer_A_configureUpMode(TIMER_A0_BASE, &upConfig);

        Timer_A_startCounter(TIMER_A0_BASE, TIMER_A_UP_MODE);
        Timer_A_initCompare(TIMER_A0_BASE, &compareConfig_PWM);
    }
}

void disable_tone() {
        Timer_A_stopTimer(TIMER_A0_BASE);
        Interrupt_disableInterrupt(INT_TA0_0);
        timerlist.timer0_type=NOT_USED;
}

void disable_timer(timerNumber timer) {
    switch(timer) {
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
        default:
            Timer_A_stopTimer(TIMER_A1_BASE);
            Interrupt_disableInterrupt(INT_TA1_0);
            timerlist.timer1_type=NOT_USED;
            break;
        }
}

void TA2_0_IRQHandler(void)
{
    Timer_A_clearCaptureCompareInterrupt(TIMER_A2_BASE,TIMER_A_CAPTURECOMPARE_REGISTER_0);
    switch(timerlist.timer2_type) {
        case DELAY:
            Timer_A_stopTimer(TIMER_A2_BASE);
            Interrupt_disableInterrupt(INT_TA2_0);
            timerlist.timer2_type=NOT_USED;
        case RATE:
            timerlist.timer2_handler();
            break;
        default:
            Timer_A_stopTimer(TIMER_A2_BASE);
            Interrupt_disableInterrupt(INT_TA2_0);
            timerlist.timer2_type=NOT_USED;
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
        default:
            Timer_A_stopTimer(TIMER_A3_BASE);
            Interrupt_disableInterrupt(INT_TA3_0);
            timerlist.timer3_type=NOT_USED;
            break;
        }
}
/* BUTTONS FUNCTIONS */
void resetButtonsState(){
    /* reset the button state */
    buttonsPressed.b1 = 0;
    buttonsPressed.b2 = 0;
    buttonsPressed.jb = 0;
}

/* BUTTONS IRQ */
// PORT3 IRQ
void PORT3_IRQHandler(void) {
    uint_fast16_t status = GPIO_getEnabledInterruptStatus(GPIO_PORT_P3); // check which pins generated the interrupt
    GPIO_clearInterruptFlag(GPIO_PORT_P3, status); // clear the interrupt flag (to clear pending interrupt indicator)
    if(status & BUT_S2_PIN){
        buttonsPressed.b2 = 1;
    }

}
// PORT4 IRQ
void PORT4_IRQHandler(void) {
    uint_fast16_t status = GPIO_getEnabledInterruptStatus(GPIO_PORT_P4); // check which pins generated the interrupt
    GPIO_clearInterruptFlag(GPIO_PORT_P4, status); // clear the interrupt flag (to clear pending interrupt indicator)
    if(status & JOY_B_PIN){
        buttonsPressed.jb = 1;
    }

}
// PORT5 IRQ
void PORT5_IRQHandler(void) {
    uint_fast16_t status = GPIO_getEnabledInterruptStatus(GPIO_PORT_P5); // check which pins generated the interrupt
    GPIO_clearInterruptFlag(GPIO_PORT_P5, status); // clear the interrupt flag (to clear pending interrupt indicator)
    if(status & BUT_S1_PIN){
        buttonsPressed.b1 = 1;
    }
}

/* ADC FUNCTIONS */
void startADCconversions(){
    ADC14_enableConversion();
    ADC14_toggleConversionTrigger();
}

void stopADCconversions(){
    ADC14_disableConversion();
}

joystick getJoyValue() {
    return JoyValues;
}

// ADC IRQ
void ADC14_IRQHandler(void){
    uint64_t status = ADC14_getEnabledInterruptStatus();
    ADC14_clearInterruptFlag(status);

    if (JOY_X_MEM & status){
        JoyValues.joyXvalue = ADC14_getResult(JOY_X_MEM)-127;    // read the adc value
        JoyValues.joyYvalue = ADC14_getResult(JOY_Y_MEM)-127;    // read the adc value
    }
    ADC14_toggleConversionTrigger();
}

/* RTC FUNCTIONS */
// RTC IRQ is in clock.c file



