#ifndef MELODY_H
#define MELODY_H
#include "notes.h"
#include "globals.h"
/*************************************************
 * Public Constants
 *************************************************/



class Melody{
  public:
    Melody(unsigned int pin);
    Melody(unsigned int pin, bool mute);
    void playMelody(int* note, int* duration);
    void muteOn();
    void muteOff();
    void setMuteMode(bool mode);
  private:
    bool _muteMode;
    unsigned int _pin;
};
extern Melody mel;
#endif
