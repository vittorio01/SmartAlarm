#include "ringtones.h" 



int get_ringtones_number() {
  return RINGTONES_NUMBER;
}

const char* get_ringtone_description(unsigned int ringtone) {
  if (ringtone>=RINGTONES_NUMBER) {
    return NULL;
  }
  return ringtones_desctiptions[ringtone];
}


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
