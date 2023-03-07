#ifndef __RINGTONES_MANAGER_H__
#define __RINGTONES_MANAGER_H__
#include <driverlib/source/ti/devices/msp432p4xx/driverlib/driverlib.h>
#include <driverlib/source/ti/devices/msp432p4xx/inc/msp.h>
#include <stdbool.h>
#include <modules/hardware/hardware.h>

#define RINGTONES_NUMBER 1
#include "ringtones/the_lick.c"

typedef struct ringtones_list{
    const uint16_t ringtones_lengths[RINGTONES_NUMBER];
    const uint16_t* ringtones_tones[RINGTONES_NUMBER];
    const uint16_t* ringtones_durations[RINGTONES_NUMBER];
    const char* ringtones_informations[RINGTONES_NUMBER];
    uint16_t currentTone;
    uint16_t selectedRingtone;
} ringtones_list;

extern ringtones_list ringtones;

typedef struct hardware_informations {
    bool piezoRunning;
    bool piezoTonePause;
    uint16_t volume;
    timerNumber usedDelayTimer;

} hardware_informations;

extern hardware_informations piezo;
void noteInterrupt();

/*ringtones_manager API*/

//All registered ringtones are associated with an ID (number from 0 to n-1 for n ringtones)

//start_ringtone starts the specified ringtone.
//The function uses the PWM timer and requires one free normal timer
bool start_ringtone(uint16_t ringtone,uint16_t volume);

//get_ringtones_number returns the number of registered ringtones
uint16_t get_ringtones_number();

//stop_ringtone stops the current ringtone
void stop_ringtone();

//get_ringtone_description returns the title of the specified ringtone
const char* get_ringtone_description(uint16_t ringtone);

#endif
