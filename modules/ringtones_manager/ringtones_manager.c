#include "ringtones_manager.h"
void ringtones_manager_intitialize(const int piezoPort, const int piezoPin) {

   int the_lick_notes[THE_LICK_DIMENSION]=THE_LICK_NOTES;
   int the_lick_durations[THE_LICK_DIMENSION]=THE_LICK_DURATIONS;
   ringtones.ringtones_informations[0]=THE_LICK_INFORMATIONS;
   ringtones.ringtones_tones[0]=the_lick_notes;
   ringtones.ringtones_durations[0]=the_lick_durations;
   ringtones.ringtones_lengths[0]=THE_LICK_DIMENSION;
   piezo.piezoPin=piezoPin;
   piezo.piezoPort=piezoPort;
   piezo.piezoRunning=false;

   piezo.compareConfig_PWM.compareInterruptEnable=TIMER_A_CAPTURECOMPARE_INTERRUPT_DISABLE;
   piezo.compareConfig_PWM.compareOutputMode=TIMER_A_OUTPUTMODE_TOGGLE_SET;
   piezo.compareConfig_PWM.compareValue=0;
   piezo.compareConfig_PWM.compareRegister=CCR_TIMER_PWM;

   piezo.upConfig_PWM.captureCompareInterruptEnable_CCR0_CCIE = TIMER_A_TAIE_INTERRUPT_DISABLE;
   piezo.upConfig_PWM.clockSource=TIMER_A_CLOCKSOURCE_SMCLK;
   piezo.upConfig_PWM.clockSourceDivider=TIMER_A_CLOCKSOURCE_DIVIDER_4;
   piezo.upConfig_PWM.timerClear=TIMER_A_DO_CLEAR;
   piezo.upConfig_PWM.timerInterruptEnable_TAIE=TIMER_A_TAIE_INTERRUPT_DISABLE;
   piezo.upConfig_PWM.timerPeriod=0;

   piezo.upConfig_note.clockSource=TIMER_A_CLOCKSOURCE_ACLK;
   piezo.upConfig_note.clockSourceDivider=TIMER_A_CLOCKSOURCE_DIVIDER_8;
   piezo.upConfig_note.timerPeriod=10;
   piezo.upConfig_note.timerInterruptEnable_TAIE=TIMER_A_TAIE_INTERRUPT_DISABLE;
   piezo.upConfig_note.captureCompareInterruptEnable_CCR0_CCIE=TIMER_A_CCIE_CCR0_INTERRUPT_ENABLE;
   piezo.upConfig_note.timerClear=TIMER_A_DO_CLEAR;


}

char* get_ringtone_description(unsigned int ringtone) {
    if (ringtone>=RINGTONES_NUMBER) {
        return "";
    }
    return ringtones.ringtones_informations[ringtone];
}

unsigned int get_ringtones_number() {
    return RINGTONES_NUMBER;
}

bool start_ringtone(unsigned int ringtone) {
    if (ringtone>=RINGTONES_NUMBER) {
        return false;
    }
    CS_setReferenceOscillatorFrequency(CS_REFO_128KHZ);
    CS_initClockSignal(CS_ACLK, CS_REFOCLK_SELECT, CS_CLOCK_DIVIDER_1);
    ringtones.currentTone=0;
    ringtones.selectedRingtone=ringtone;
    Interrupt_disableMaster();
    GPIO_setAsPeripheralModuleFunctionOutputPin(piezo.piezoPort, piezo.piezoPin,GPIO_PRIMARY_MODULE_FUNCTION);
    Timer_A_configureUpMode(DEVICE_TIMER_PWM, &piezo.upConfig_PWM);
    Timer_A_startCounter(DEVICE_TIMER_PWM, TIMER_A_UP_MODE);
    Timer_A_initCompare(DEVICE_TIMER_PWM, &piezo.compareConfig_PWM);

    Timer_A_configureUpMode(DEVICE_TIMER_NOTE, &piezo.upConfig_note);
    Timer_A_registerInterrupt(DEVICE_TIMER_NOTE, TIMER_A_CCR0_INTERRUPT,noteInterrupt);
    Timer_A_enableInterrupt(DEVICE_TIMER_NOTE);
    Timer_A_startCounter(DEVICE_TIMER_PWM, TIMER_A_UP_MODE);
    piezo.piezoRunning=true;
    Interrupt_enableMaster();
    return true;
}

void stop_ringtone() {
    piezo.piezoRunning=false;
}

void noteInterrupt() {
    Timer_A_clearCaptureCompareInterrupt(DEVICE_TIMER_NOTE,TIMER_A_CAPTURECOMPARE_REGISTER_0);
    if (piezo.piezoRunning==false) {
        Timer_A_stopTimer(DEVICE_TIMER_PWM);
        Timer_A_stopTimer(DEVICE_TIMER_NOTE);
    } else {
        Timer_A_setCompareValue(DEVICE_TIMER_NOTE,TIMER_A_CAPTURECOMPARE_REGISTER_0,ringtones.ringtones_durations[ringtones.selectedRingtone][ringtones.currentTone]);
        Timer_A_setCompareValue(DEVICE_TIMER_PWM,TIMER_A_CAPTURECOMPARE_REGISTER_0,ringtones.ringtones_tones[ringtones.selectedRingtone][ringtones.currentTone]);
        ringtones.currentTone=(ringtones.currentTone+1)%(ringtones.ringtones_lengths[ringtones.selectedRingtone]);
    }

}
