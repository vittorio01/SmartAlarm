#ifndef __RINGTONES_MANAGER_H__
#define __RINGTONES_MANAGER_H__
#include <driverlib/source/ti/devices/msp432p4xx/driverlib/driverlib.h>
#include <driverlib/source/ti/devices/msp432p4xx/inc/msp.h>
#include <stdbool.h>
#include <modules/hardware/hardware.h>

#include "ringtones/the_lick.h"
#define RINGTONES_NUMBER 1


typedef struct ringtones_list{
    uint16_t ringtones_lengths[RINGTONES_NUMBER];
    uint16_t* ringtones_tones[RINGTONES_NUMBER];
    uint16_t* ringtones_durations[RINGTONES_NUMBER];
    char* ringtones_informations[RINGTONES_NUMBER];
    uint16_t currentTone;
    uint16_t selectedRingtone;
} ringtones_list;


typedef struct hardware_informations {
    uint16_t piezoPin;
    uint16_t piezoPort;
    bool piezoRunning;
    bool piezoTonePause;
    uint16_t volume;
    timerNumber usedDelayTimer;
    timerNumber usedPWMTimer;

} hardware_informations;

hardware_informations piezo;
ringtones_list ringtones;

void ringtones_manager_initialize(const uint16_t piezoPort, const uint16_t piezoPin);
bool start_ringtone(uint16_t ringtone,uint16_t volume);
uint16_t get_ringtones_number();
void stop_ringtone();
char* get_ringtone_description(uint16_t ringtone);
void noteInterrupt();

#endif
