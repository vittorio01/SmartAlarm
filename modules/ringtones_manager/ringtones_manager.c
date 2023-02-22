#include "ringtones_manager.h"
void ringtones_manager_intitialize(const uint16_t piezoPort, const uint16_t piezoPin) {

   uint16_t the_lick_notes[THE_LICK_DIMENSION]=THE_LICK_NOTES;
   uint16_t the_lick_durations[THE_LICK_DIMENSION]=THE_LICK_DURATIONS;
   ringtones.ringtones_informations[0]=THE_LICK_INFORMATIONS;
   ringtones.ringtones_tones[0]=the_lick_notes;
   ringtones.ringtones_durations[0]=the_lick_durations;
   ringtones.ringtones_lengths[0]=THE_LICK_DIMENSION;
   piezo.piezoPin=piezoPin;
   piezo.piezoPort=piezoPort;
   piezo.piezoRunning=false;
   piezo.usedDelayTimer=NONE;
   piezo.usedPWMTimer=NONE;
}

char* get_ringtone_description(uint16_t ringtone) {
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
    piezo.piezoTonePause=false;
    ringtones.selectedRingtone=ringtone;
    piezo.volume=volume;

    piezo.usedPWMTimer=generate_pwm(ringtones.ringtones_tones[ringtones.selectedRingtone][0],piezo.volume,piezo.piezoPort,piezo.piezoPin);
    if (piezo.usedPWMTimer==NONE) return false;
    piezo.usedDelayTimer=generate_delay(ringtones.ringtones_durations[ringtones.selectedRingtone][0],noteInterrupt);
    if (piezo.usedDelayTimer==NONE) return false;
    piezo.piezoRunning=true;
    return true;
}

void stop_ringtone() {
    piezo.piezoRunning=false;
}

void noteInterrupt() {
    disable_timer(piezo.usedPWMTimer);
    if (piezo.piezoRunning==true) {
        if (piezo.piezoTonePause) {
            piezo.usedDelayTimer=generate_delay(NOTE_DIVISION_DURATION,noteInterrupt);
        } else {
            piezo.usedPWMTimer=generate_pwm(ringtones.ringtones_tones[ringtones.selectedRingtone][ringtones.currentTone],piezo.volume,piezo.piezoPort,piezo.piezoPin);
            piezo.usedDelayTimer=generate_delay(ringtones.ringtones_durations[ringtones.selectedRingtone][ringtones.currentTone],noteInterrupt);
            ringtones.currentTone=(ringtones.currentTone+1)%(ringtones.ringtones_lengths[ringtones.selectedRingtone]);
        }
    }
}
