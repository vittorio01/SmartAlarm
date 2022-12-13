#include "ringtones.h" 

const int* ringtones_tones[RINGTONES_NUMBER]={nokia_ringtone};
const unsigned int ringtones_durations[RINGTONES_NUMBER]={NOKIA_TONES_NUMBER};
const char* ringtones_descriptions[RINGTONES_NUMBER]={NOKIA_DESCRIPTION};


int get_ringtones_number() {
  return RINGTONES_NUMBER;
}

const char* get_ringtone_description(unsigned int ringtone) {
  if (ringtone>=RINGTONES_NUMBER) {
    return "";
  }
  return ringtones_descriptions[ringtone];
}

/*
void start_ringtone(unsigned int piezoPin) {
  ring_on = true;
  selectedPiezoPin=piezoPin;
  selectedRingtone = random(RINGTONES_NUMBER);
  selectedRingtoneDuration = ringtones_durations[selectedRingtone];
  currentTone=0;
  ringtone_Timer.begin(&toneHandler,200);
  ringtone_Timer.start();
}

bool start_ringtone(unsigned int piezoPin,unsigned int ringtone) {
  if (ringtone>RINGTONES_NUMBER) {
    return false;
  }
  ring_on = true;
  selectedRingtone = ringtone;
  selectedRingtoneDuration = ringtones_durations[selectedRingtone];
  selectedPiezoPin=piezoPin;
  currentTone=0;
  ringtone_Timer.begin(&toneHandler,200);
  ringtone_Timer.start();
  return true;
}


void stop_ringtone() {
  ring_on=false;
}
*/
