#include <Arduino.h>
#ifndef XINPOUT_H
#define XINPOUT_H

typedef enum {
  BT_UP,
  BT_DOWN,
  BT_LEFT,
  BT_RIGHT,
  BT_BACK,
  BT_VALID,
  BT_NONE
} XButtonId;

typedef struct {
  unsigned int pin;
  XButtonId id;
} XButton;
class XInput{
  public:
    XInput(XButton but[],int nbElem);
    void begin();
    XButtonId readButtons(void);
    void printButtons();
  private:
    XButton *_buttons;
    int _nbButtons;
    
};

#endif
