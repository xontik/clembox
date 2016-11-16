#include "stages.h"
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
  stageValue++;
  mel.playMelody(sucessStageMel,sucessStageDuration);
  
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
  stageValue++;
  mel.playMelody(sucessStageMel,sucessStageDuration);
}


void doStage(int v){
  switch(v){
    case 1:
      stage1();
      break;
    case 2:
      stage2();
      break;
  }
}
