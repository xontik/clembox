#include "XInput.h"
#include <Arduino.h>

XInput::XInput(XButton* b){
  
  this->_buttons = b;  
}
void XInput::begin(){
  int i=0;
  while(_buttons[i].pin != -1){
    pinMode(_buttons[i].pin, INPUT);
    i++;
  }
}
void XInput::printButtons(){
  Serial.print("Buttons states at");
  Serial.println(millis());
  int i=0;
  while(_buttons[i].pin != -1){
    Serial.println(digitalRead(this->_buttons[i].pin));
    i++;
  }
}
XButtonId XInput::buttonPushed(){
  XButtonId btn;
    while (readButtons() != BT_NONE);
    
    // Attente appuie btn 
    while ((btn = readButtons()) == BT_NONE);
    
    delay(30);
    //Fin anti rebons 
    // Attente relache tout les boutons
    while (readButtons() != BT_NONE);
    return btn;
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
        Serial.print("Button pin : ");
        Serial.println(this->_buttons[i].pin);
      }
    }
    if(nbTrue != 1){
      return BT_NONE;
    }else{
      return b;
    }
  }

}

