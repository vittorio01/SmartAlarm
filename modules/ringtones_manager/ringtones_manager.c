#include <modules/ringtones_manager/ringtones/the_lick.c>
#include "ringtones_manager.h"

const uint16_t the_lick_notes[THE_LICK_DIMENSION]=THE_LICK_NOTES;
const uint16_t the_lick_durations[THE_LICK_DIMENSION]=THE_LICK_DURATIONS;

ringtones_list ringtones={
    {THE_LICK_DIMENSION},
    {the_lick_notes},
    {the_lick_durations},
    {THE_LICK_INFORMATIONS},
    0,
    0
};

hardware_informations piezo={
     false,
     false,
     0,
     NONE
};

const char* get_ringtone_description(uint16_t ringtone) {
    if (ringtone>=RINGTONES_NUMBER) {
        return "";
    }
    return ringtones.ringtones_informations[ringtone];
}

uint16_t get_ringtones_number() {
    return RINGTONES_NUMBER;
}

bool start_ringtone(uint16_t ringtone,uint16_t volume) {
    if (ringtone>=RINGTONES_NUMBER) {
        return false;
    }

    ringtones.currentTone=0;
    piezo.piezoTonePause=true;
    ringtones.selectedRingtone=ringtone;
    piezo.volume=volume;
    piezo.piezoRunning=true;
    piezo.usedDelayTimer=generate_delay(ringtones.ringtones_durations[ringtones.selectedRingtone][0],&noteInterrupt);
    if (piezo.usedDelayTimer==NONE) {
        piezo.piezoRunning=false;
        return false;
    }

    return true;
}

void stop_ringtone() {
    piezo.piezoRunning=false;
}

void noteInterrupt() {
    if (piezo.piezoRunning==true) {
        if (piezo.piezoTonePause) {
            disable_tone();
            piezo.usedDelayTimer=generate_delay(NOTE_DIVISION_DURATION,&noteInterrupt);
            piezo.piezoTonePause=false;
        } else {
            generate_tone(ringtones.ringtones_tones[ringtones.selectedRingtone][ringtones.currentTone],piezo.volume);
            piezo.usedDelayTimer=generate_delay(ringtones.ringtones_durations[ringtones.selectedRingtone][ringtones.currentTone],&noteInterrupt);
            ringtones.currentTone=(ringtones.currentTone+1)%(ringtones.ringtones_lengths[ringtones.selectedRingtone]);
            piezo.piezoTonePause=true;
        }
    } else {
        disable_tone();
    }
}
