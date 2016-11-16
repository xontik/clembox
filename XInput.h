#include <Arduino.h>
#ifndef XINPOUT_H
#define XINPOUT_H

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
    void begin();
    XButtonId readButtons(void);
    XButtonId buttonPushed(void);
    void printButtons();
  private:
    XButton *_buttons;
    int _nbButtons;
    
};

#endif
