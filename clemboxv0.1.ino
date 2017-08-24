

//#include <Streaming.h>
#include "globals.h"
#include "Melody.h"
#include "XInput.h"

#include "Menu.h"
#include "stages.h"
#include <EEPROM.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

//#define TESTSTAGE


void setup() {
  
  /* Initialisation des pin --------------------------------------*/
  //OUTPUT
  pinMode(relayOpenPin,OUTPUT);
  pinMode(piezoMelodyPin,OUTPUT);
  //INPUT
  pinMode(usbKeyPresenceCheck,INPUT);
  
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
  stageValue = EEPROM.read(stageAdress);
  
  /* RELAYS ---------------------*/
  digitalWrite(relayOpenPin,HIGH);
  
  /* Sequence allumage --------------------------------------*/
  mel.playMelody(startMel,startDuration);
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



