
#include <Streaming.h>
#include "globals.h"
#include "Melody.h"
#include "XInput.h"
#include <EEPROM.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include "XMenu.h"

#define WIN 3
#define START 1

XInput input(buttons);

Melody mel(piezoMelodyPin,true);


LiquidCrystal_I2C lcd(0x27,20,4);  



void setup() {
  /* Initialisation des pin --------------------------------------*/
  pinMode(resetStagePin,INPUT);
  /* Initialisation des composant --------------------------------------*/
  /* Serial ------------------------------------------------------------*/
  Serial.begin(9600);
  Serial.setTimeout(0);
  Serial.println("<-- Power on ! -->");
  /* Buttons--------------------------------------*/
  input.begin();
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
  doMenu(mainMenu);
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

void doMenu(XMenu menu) {
  XButtonId button;
  bool keephere = true;
  int choice =1;
  while(keephere){
    displayMenu(menu,&lcd,choice);
   
    // Wait relache boutons 
    while (input.readButtons() != BT_NONE);
    
    // Attente appuie btn 
    while ((button = input.readButtons()) == BT_NONE);
    
    delay(30);
    //Fin anti rebons 
    // Attente relache tout les boutons
    while (input.readButtons() != BT_NONE);
    //gestions des differents cas
    switch(button){
      case BT_UP:
        choice++;
      break;
      case BT_DOWN:
        choice--;
      break;
      case BT_LEFT:
        keephere = false;
      break;
      case BT_RIGHT:
      case BT_VALID:
        menu.calbackFct(choice);
      break;
    }
    if(choice > menu.nbItems){
      choice = 1;
    }
    if(choice < 1){
      choice = menu.nbItems;
    }
  }
}



/*
 * Etape : 1
 * But : Presentation puis Appuyer sur un bouton
 * Composant mis en jeu : - bouton
 * Pins mis en jeu: - simpleButtonPin
 */
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
void win(){
  lcd.clear();
  lcd.setCursor(7,1);
  lcd.print("WIN!");
  
  while(1){
    delay(500);
    Serial.println("WIN");
  }
  
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


