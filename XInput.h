#ifndef XINPOUT_H
#define XINPOUT_H
#include <Arduino.h>
#include "globals.h"




class XInput{
  public:
    XInput(byte but[]);
    byte readButtons(void);
    byte buttonPushed(void);
    byte lastButtonPushed(void);

    void printButtons();
  private:
    byte *_buttons;
    
};
extern XInput input;
#endif
