#include "ringtones.h" 

int get_ringtone_number() {
  return RINGTONES_NUMBER;
}

const char* get_ringtone_description(unsigned int ringtone) {
  if (ringtone>=RINGTONES_NUMBER) {
    return NULL;
  }
  return ringtones_desctiptions[ringtone];
}

void tone_handler() {
  ringtoneTimer.stop();
   if (ring_on) {
     currentTone=(currentTone+2)%selectedRingtoneDuration;
     tone(selectedPiezoPin,ringtones_tones[selectedRingtone][currentTone],ringtones_tones[selectedRingtone][currentTone+1]*0.9);
     ringtoneTimer.begin(tone_handler,ringtones_tones[selectedRingtone][currentTone+1]);
     ringtoneTimer.start();
   } 
}

void start_ringtone(unsigned int piezoPin) {
  ring_on = true;
  selectedPiezoPin=piezoPin;
  selectedRingtone = TrueRandom.random(RINGTONES_NUMBER);
  selectedRingtoneDuration = ringtones_durations[selectedRingtone];
  currentTone=0;
  ringtoneTimer.begin(tone_handler,200);
  ringtoneTimer.start();
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
  ringtoneTimer.begin(tone_handler,200);
  ringtoneTimer.start();
  return true;
}
 
void stop_ringtone() {
  ring_on=false;
}
