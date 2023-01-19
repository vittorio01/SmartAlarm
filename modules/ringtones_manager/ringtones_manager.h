#ifndef __RINGTONES_MANAGER_H__
#define __RINGTONES_MANAGER_H__
#include <stdbool.h>
#include <ti/devices/msp432p4xx/inc/msp.h>
#include <ti/devices/msp432p4xx/driverlib/driverlib.h>

#include "ringtones/the_lick.h"
#define RINGTONES_NUMBER 1

#define DEVICE_TIMER_PWM        TIMER_A0_BASE
#define CCR_TIMER_PWM           TIMER_A_CAPTURECOMPARE_REGISTER_4
#define DEVICE_TIMER_NOTE       TIMER_A1_BASE

typedef struct ringtones_list{
    int ringtones_lengths[RINGTONES_NUMBER];
    int* ringtones_tones[RINGTONES_NUMBER];
    int* ringtones_durations[RINGTONES_NUMBER];
    char* ringtones_informations[RINGTONES_NUMBER];
    int currentTone;
    int selectedRingtone;
} ringtones_list;


typedef struct hardware_informations {
    int piezoPin;
    int piezoPort;
    bool piezoRunning;
    Timer_A_CompareModeConfig compareConfig_PWM;
    Timer_A_UpModeConfig upConfig_PWM;
    Timer_A_UpModeConfig upConfig_note;
} hardware_informations;

hardware_informations piezo;
ringtones_list ringtones;

void ringtones_manager_intitialize(const int piezoPort, const int piezoPin);
bool start_ringtone(unsigned int ringtone);
unsigned int get_ringtones_number();
void stop_ringtone();
char* get_ringtone_description(unsigned int ringtone);
void noteInterrupt();

#endif
