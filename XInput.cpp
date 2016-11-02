#include "XInput.h"
#include <Arduino.h>

XInput::XInput(XButton* b,int nbElem){
  
  this->_buttons = b;  
  this->_nbButtons = nbElem;
}
void XInput::begin(){
  int i;
  for(i=0;i<_nbButtons;i++){
    pinMode(_buttons[i].pin, INPUT);
  }
}
void XInput::printButtons(){
  Serial.println("Buttons states :");
  int i;
  for(i=0;i<_nbButtons;i++){
    Serial.println(digitalRead(this->_buttons[i].pin));
  }
}
XButtonId XInput::readButtons(){
  int i;
  int nbTrue = 0;
  int s;
  
  XButtonId b;
  if(Serial.available() > 0){
      s = Serial.parseInt();
      Serial.print ("Button pressed by Serial : ");
      Serial.println(this->_buttons[s].pin);

      return this->_buttons[s].id;
      
  }
  else{
    for(i=0;i<_nbButtons;i++){
      if(digitalRead(this->_buttons[i].pin)){
        nbTrue++;
        b=this->_buttons[i].id;
      }
    }
  }
  if(nbTrue != 1){
    return BT_NONE;
  }else{
    return b;
  }
}

