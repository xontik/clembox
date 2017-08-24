#include "Melody.h"
#include <Arduino.h>
Melody::Melody(unsigned int pin){
  _pin = pin;
  _muteMode = false;
  pinMode(_pin,OUTPUT);
}
Melody::Melody(unsigned int pin, bool mute){
  _muteMode = mute;
  _pin = pin;
  pinMode(_pin,OUTPUT);
  
}

void Melody::playMelody(int* note, int* duration){
  if(_muteMode){
    return;
  }else{
    int i=0;
    int noteDuration;
    while(note[i]!=NOTE_END){
    noteDuration = 1000 / duration[i];
    tone(_pin, note[i], noteDuration);
    delay(noteDuration * 1.20);
    // stop the tone playing:
    noTone(_pin);
    i++;
    }
  }
}
void Melody::muteOn(){
  _muteMode = true;

}
void Melody::muteOff(){
  _muteMode = false;
}

void Melody::setMuteMode(bool mode){
    _muteMode = mode;
}

Melody mel(piezoMelodyPin);
