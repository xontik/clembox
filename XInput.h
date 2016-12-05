#ifndef XINPOUT_H
#define XINPOUT_H
#include <Arduino.h>
#include "globals.h"

typedef enum {
  BT_UP,
  BT_DOWN,
  BT_LEFT,
  BT_RIGHT,
  BT_VALID,
  BT_NONE
} XButtonId;

typedef struct {
  int pin;
  XButtonId id;
} XButton;

class XInput{
  public:
    XInput(XButton but[]);
    XButtonId readButtons(void);
    XButtonId buttonPushed(void);
    XButtonId lastButtonPushed(void);
    void printButtons();
  private:
    XButton *_buttons;
    
};
extern XInput input;
#endif
