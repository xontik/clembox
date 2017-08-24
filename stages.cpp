#include "stages.h"

bool (*stageTab[3])() = {stage1,stage2,stage3};

bool stage1(){

  XButtonId button;
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Trouve le bon bouton !");
  lcd.setCursor(0,2);
  lcd.print("Et appuie dessus !");
  button = BT_NONE;
  while( button != BT_LEFT){
    button = input.buttonPushed();
    if(button == BT_VALID){
      return false;
    }
  }
  return true;
  
}
/*
 * Etape : 2
 * But : Soulever la boite
 * Composant mis en jeu : - resistance lumineuse
 * Pins mis en jeu: - lumresitancepin
 */

bool stage2(){
  int lightSensorValue;
  XButtonId button;
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("La levitation est...");
  lcd.setCursor(0,1);
  lcd.print("... La solution !");
  lcd.setCursor(0,3);
  lcd.print("(A faire de jour !)");
  
 
  button = BT_NONE;
  while(button != BT_VALID){     
     
     if(getLight(bottomLightSensor1) >= LOW_LIGHT){
        return true;
     }
     button = input.lastButtonPushed();
    delay(100);
  }
  return false;

  
}
bool stage3(){
  int val1,val2,val3;
  
  XButtonId button;
  lcd.clear();
  lcd.print("Atteinds le bon nombre :");
  
  
  button = BT_NONE;
  while(button != BT_VALID){     
     
     
     val1 = analogRead(leftPotLeft);    
     val2 = analogRead(leftPotMid);    
     val3 = analogRead(leftPotRight);
     lcd.setCursor(0,2);
     lcd.print("d");
     button = input.lastButtonPushed();
  }
  return false;

  
}
void win(){
  lcd.clear();
  lcd.setCursor(7,1);
  lcd.print("WIN!");
 
  
  while(1){
    
    Serial.println("WIN");
    if(input.buttonPushed()!=BT_VALID){
      digitalWrite(relayOpenPin,LOW);
      delay(2000);
      digitalWrite(relayOpenPin,HIGH);
      
    }
    else{
      return;
    }
  }
 
  
}


bool doStage(int v){
  Serial.println("doStage");
  if(v == NB_STAGE+1){
      win();
      //stageValue = START;
      //EEPROM.write(stageAdress,stageValue);
      return false;
   }else{
    return stageTab[v-1]();
   }
  
}
