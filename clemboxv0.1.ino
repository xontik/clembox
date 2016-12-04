

//#include <Streaming.h>
#include "globals.h"
#include "Melody.h"
#include "XInput.h"

#include "Menu.h"
#include "stages.h"
#include <EEPROM.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>




void setup() {
  
  /* Initialisation des pin --------------------------------------*/
  pinMode(resetStagePin,INPUT);
  pinMode(relayOpenPin,OUTPUT);
  digitalWrite(relayOpenPin,HIGH);
  /* Initialisation des composant --------------------------------------*/
  /* Serial ------------------------------------------------------------*/
  Serial.begin(9600);
  Serial.setTimeout(0);
  Serial.println("<-- Power on ! -->");

  /* LCD --------------------------------------*/
  lcd.begin();
  lcd.backlight();
  lcd.createChar(ARROW_RIGHT,rightArrow);
  lcd.createChar(ARROW_LEFT,leftArrow);
  lcd.createChar(ARROW_UP,upArrow);
  lcd.createChar(ARROW_DOWN,downArrow);
  /* EEPROM --------------------------------------*/
  if(digitalRead(resetStagePin) == HIGH){
    stageValue = START;
    EEPROM.write(stageAdress,stageValue);
    Serial.println("Stages Reseted");
  }else{
    stageValue = EEPROM.read(stageAdress);
  }
  //mel.setMuteMode(EEPROM.read(soundAdress));
  mel.muteOff();
  /* beep de debut --------------------------------------*/
  mel.playMelody(startMel,startDuration);
  /* value de depart --------------------------------------*/
  lcd.setCursor(5,0);
  lcd.print("Bienvenue !");
  delay(1000);
  /* pour le debug --------------------------------------*/
  #ifdef TESTSTAGE
  doStage(TESTSTAGE);
  #endif
  /* ------- choix pour les menu ----- */
}
void loop(){
  Serial.println("Loop");
  mainMenu();
}



