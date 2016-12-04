#include "stages.h"

void (*stageTab[2])() = {stage1,stage2};

void stage1(){
  

  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Trouve le mega bouton !");
  lcd.setCursor(0,2);
  lcd.print("Et appuie dessus !");
  while(stayInThisStage){
      if(input.readButtons() == BT_VALID)
        stayInThisStage = false;
      
      
  }
  
}
/*
 * Etape : 2
 * But : Soulever la boite
 * Composant mis en jeu : - resistance lumineuse
 * Pins mis en jeu: - lumresitancepin
 */

void stage2(){
  int lightSensorValue;

  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("La levitation est...");
  lcd.setCursor(0,1);
  lcd.print("... La solution !");
  lcd.setCursor(0,3);
  lcd.print("(A faire de jour !)");
  
  while(stayInThisStage){
     lightSensorValue = analogRead(lightSensorPin);
     Serial.print("Sensor value:");
     Serial.println(lightSensorValue);
     if(lightSensorValue >= 600){
        stayInThisStage = false;
     }
    delay(100);
  }

  
}
void win(){
  lcd.clear();
  lcd.setCursor(7,1);
  lcd.print("WIN!");
 
  
  while(1){
    delay(500);
    Serial.println("WIN");
    if(input.buttonPushed()==BT_VALID){
      digitalWrite(relayOpenPin,LOW);
      delay(2000);
      digitalWrite(relayOpenPin,HIGH);
    }
  }
  
}


bool doStage(int v){
  Serial.println("doSTage");
  win();
}
