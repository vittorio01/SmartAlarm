#include "ringtones.h" 

const int* ringtones_tones[RINGTONES_NUMBER]={nokia_ringtone};
const unsigned int ringtones_durations[RINGTONES_NUMBER]={NOKIA_TONES_NUMBER};
const char* ringtones_descriptions[RINGTONES_NUMBER]={NOKIA_DESCRIPTION};

void ringtone_duration_interrupt_timer() {
    Timer_A_clearCaptureCompareInterrupt(TIMER_A1_BASE,TIMER_A_CAPTURECOMPARE_REGISTER_0);
    if (ring_on==true) {
        currentTone=(currentTone%selectedRingtoneDuration)+2
        upConfig_PWM.timerPeriod=ringtones_tones[selectedRingtone][currentTone];
        upConfig_DUR.timerPeriod=ringtones_toned[selectedRingtone][currentTone+1];
        Timer_A_configureUpMode(PWM_TIMER, &upConfig);
        Timer_A_configureUpMode(DURATION_TIMER, &upConfig);
    } else {
        Timer_A_unregisterInterrupt(DURATION_TIMER);
        Timer_A_disableInterrupt(DURATION_TIMER);
    }
}

int get_ringtones_number() {
  return RINGTONES_NUMBER;
}

const char* get_ringtone_description(unsigned const int ringtone) {
  if (ringtone>=RINGTONES_NUMBER) {
    return "";
  }
  return ringtones_descriptions[ringtone];
}

void startRandomRingtone() {
    ring_on=true;
}
bool startSpecifiedRingtone(unsigned const int ringtone) {
    if (ringtone>=RINGTONES_NUMBER) {
        return false;
    }
    selectedRingtone=ringtone;
    selectedRingtoneDuration=ringtones_durations[ringtone]
    currentTone=0;
    GPIO_setAsPeripheralModuleFunctionOutputPin(BUZZER_PORT, BUZZER_PIN, GPIO_PRIMARY_MODULE_FUNCTION);
    compareConfig_PWM = {
            PWM_CAPTURE_COMPARE_REGISTER,
            TIMER_A_CAPTURECOMPARE_INTERRUPT_DISABLE,
            TIMER_A_OUTPUTMODE_TOGGLE_SET,
            (int) 65536*DEFAULT_VOLUME/100
    };
    upConfig_PWM = {
            TIMER_A_CLOCKSOURCE_DIVIDER_12,         // SMCLK/12 = 250 KhZ
            ringtones_tones[ringtone][currentTone],
            TIMER_A_TAIE_INTERRUPT_DISABLE,
            PWM_CAPTURE_COMPARE_REGISTER_INTERRUPT,
            TIMER_A_DO_CLEAR
            };

    upConfig_DUR =
    {
            TIMER_A_CLOCKSOURCE_SMCLK,
            TIMER_A_CLOCKSOURCE_DIVIDER_64,         // SMCLK/1 = 3MHz
            ringtones_tones[ringtone][currentTone+1],                           // every half second
            TIMER_A_TAIE_INTERRUPT_DISABLE,         // Disable Timer interrupt
            DUR_CAPTURE_COMPARE_REGISTER_INTERRUPT ,    // Enable CCR0 interrupt
            TIMER_A_DO_CLEAR                        // Clear value
    };

    Timer_A_configureUpMode(PWM_TIMER, &upConfig);
    Timer_A_startCounter(PWM_TIMER , TIMER_A_UP_MODE)
    Timer_A_initCompare(PWM_TIMER , &compareConfig_PWM);
    Timer_A_configureUpMode(DURATION_TIMER, &upConfig);
    Timer_A_registerInterrupt(DURATION_TIMER,TIMER_A_CCRX_AND_OVERFLOW_INTERRUPT,&ringtone_duration_interrupt_timer);
    Timer_A_enableInterrupt(DURATION_TIMER);
    ring_on=true;
}
void stopRingtone() {
    ring_on=false;
}
