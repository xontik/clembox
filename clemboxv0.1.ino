
#include <Streaming.h>


#include "Melody.h"
#include "XInput.h"
#include <EEPROM.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

#include "XMenu.h"

#define WIN 3
#define START 1

#define ARROW_UP 2
#define ARROW_DOWN 3
#define ARROW_LEFT 1
#define ARROW_RIGHT 0
//#define TESTSTAGE 2

/*
 * Sketch pour la boite a énigme de clem
 * v0.1
 */
/* buttons */
XButton buttons[] = {
  {24,BT_UP},
  {25,BT_DOWN},
  {26,BT_LEFT},
  {27,BT_RIGHT},
  {28,BT_BACK},
  {29,BT_VALID},
  
  };
XInput input(buttons,6);


/* input Pins */
byte lightSensorPin = A1;

/* output Pins */
byte piezoMelodyPin = 48;
/* EEPROM */
/*
 * 2 -> sound adress
 * 5 -> partie 1
 * 6 -> partie 2
 * 7 -> partie 3
 * 11 -> adress partie courante
 * 
 */
/* reset EEPROM Pin */
byte resetStagePin = 22;

/* EEPROM Variable */
int currentGameAdress = 10;
int stageAdress = 5;
int soundAdress = 2;
byte tmpStageValue;
byte stageValue;
bool stayInThisStage = true;

/* Melodys */
int sucessStageMel[] = {NOTE_F4,NOTE_FS4,NOTE_G4,NOTE_GS4,NOTE_END};
int sucessStageDuration[] = {6, 6, 6, 2};
int startMel[] = {NOTE_C5,NOTE_END};
int startDuration[] = {1};
int melody[] = {NOTE_C4, NOTE_G3, NOTE_G3, NOTE_A3, NOTE_G3, 0, NOTE_B3, NOTE_C4};
int dur[] = {4, 8, 8, 4, 4, 4, 4, 4};
Melody mel(piezoMelodyPin,true);

/* LCD*/
LiquidCrystal_I2C lcd(0x27,20,4);  
/* Custom char*/
byte rightArrow[8] = {B00000,B00100,B00010,B11111,B00010,B00100,B00000,};
byte leftArrow[8] = {B00000,B00100,B01000,B11111,B01000,B00100,B00000,};
byte upArrow[8] = {B00100,B01110,B10101,B00100,B00100,B00100,B00000,};
byte downArrow[8] = {B00000,B00100,B00100,B00100,B10101,B01110,B00100,};

/* XMenu init*/
void doMainMenu(uint8_t selected);
void doSubMenu(uint8_t selected);

static const char* mainMenuItems[] = { "MTest 1", "MTest 2", "MTest 3", "MTest 4"};
static const XMenu mainMenu = {
  "Menu Principal",
  mainMenuItems,
  4,
  &doMainMenu
};
static const char* subMenuItems[] = { "Test 1", "Test 2", "Test 3", "Test 4"};
static const XMenu subMenu = {
  "Menu Secondaire",
  subMenuItems,
  4,
  &doSubMenu
};
/* ------- choix pour les menu ----- */
int choice;

void setup() {
  /* Initialisation des pin --------------------------------------*/
  pinMode(resetStagePin,INPUT);
  /* Initialisation des composant --------------------------------------*/
  /* Serial ------------------------------------------------------------*/
  Serial.begin(9600);
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
  choice = 1;
}
void loop(){
  doMenu(mainMenu);
}
void doMenu(XMenu menu) {
  XButtonId button;
  displayMenu(menu,choice);
  Serial.print("Choice : ");
  Serial.println(choice);
  Serial.println("Wait relache boutons");
  while (input.readButtons() != BT_NONE);
  lcd.clear();
  Serial.println("Attente appuie btn");
  while ((button = input.readButtons()) == BT_NONE);
  
  delay(30);
  Serial.println("Fin anti rebons");
  Serial.println("Attente relache tout les boutons");
  while (input.readButtons() != BT_NONE);
  switch(button){
    case BT_UP:
      Serial.println("++");
      choice++;
    break;
    case BT_DOWN:
      Serial.println("++");
      choice--;
    break;
    case BT_LEFT:
      return;
    break;
    case BT_RIGHT:
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
void doMainMenu(uint8_t selected){
  Serial.println("in doMainMenu()");
  if(selected == 1){
    choice = 1;
    displayMenu(subMenu,choice);
  }else{
    Serial.print("PAS 1");
  }
  
}
void doSubMenu(uint8_t selected){
  
}


