#include <Streaming.h>
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


void play(){
  stayInThisStage = true; /* on repasse forcement a true pour le prochaine appel aune etape */
  /*on compare la nouvelle valeur avec l'eeprom si changement on ecrit dans l'epprom */
  tmpStageValue = EEPROM.read(stageAdress);
  if(stageValue < tmpStageValue ){
    stageValue = tmpStageValue;
  }else if (stageValue != tmpStageValue){
    EEPROM.write(stageAdress,stageValue);
  }

  Serial.print("Stage value : ");
  Serial.println(stageValue);
  
  /* on renvoie sur la fonction gerant l'etape courante */
  Serial.print("Etape : ");
  Serial.println(stageValue);

  doStage(stageValue);
  if(stageValue == WIN){
    EEPROM.write(stageAdress,stageValue);
    win();
  }else{
    lcd.clear();
    lcd.setCursor(7,0);
    lcd.print("Bravo !");
    lcd.setCursor(0,2);
    lcd.print("Enigme suivante ");
    delay(500);
    lcd.print(".");
    delay(500);
    lcd.print(".");
    delay(500);
    lcd.print(".");
    delay(500);
  }
}




/*
 * Etape : 1
 * But : Presentation puis Appuyer sur un bouton
 * Composant mis en jeu : - bouton
 * Pins mis en jeu: - simpleButtonPin
 */
void win(){
  lcd.clear();
  lcd.setCursor(7,1);
  lcd.print("WIN!");
  
  while(1){
    delay(500);
    Serial.println("WIN");
  }
  
}
