#include "XInput.h"
#include <Arduino.h>

XInput::XInput(byte* b){
  this->_buttons = b; 
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
    Serial.println("All button of");
    
    // Attente appuie btn 
    btn = BT_NONE;
    while (btn == BT_NONE){
      
      btn = readButtons();
      
    }
    Serial.println("On button pushed");
    
    delay(30);
    //Fin anti rebons 
    // Attente relache tout les boutons
    while (readButtons() != BT_NONE);
    return btn;
}
XButtonId XInput::lastButtonPushed(){
 XButtonId btn = BT_NONE;
    btn = readButtons();
    delay(30);
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
    
    i=0;
    while(this->_buttons[i].pin != -1){
      if(digitalRead(this->_buttons[i].pin)){
        nbTrue++;
        b=this->_buttons[i].id;
        Serial.print("Button pin : ");
        Serial.println(this->_buttons[i].pin);
        
      }
      i++;
    }
    if(nbTrue != 1){
      return BT_NONE;
    }else{
      return b;
    }
  }

}

XInput input(buttons);
