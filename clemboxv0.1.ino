
#include <Streaming.h>
#include "Melody.h"
#include "XInput.h"
#include <EEPROM.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

#include "XMenu.h"

#define WIN 3
#define START 1


//#define TESTSTAGE 2

/*
 * Sketch pour la boite a énigme de clem
 * v0.1
 */
/* buttons */
XButton buttons[] = {
  {24,BT_UP},
  {25,BT_DOWN},
  {23,BT_LEFT},
  {22,BT_RIGHT},
  {27,BT_VALID}
  
  };
XInput input(buttons,5);


/* input Pins */
byte lightSensorPin = A1;

/* output Pins */
byte piezoMelodyPin = 48;
/* EEPROM */
/*
 * 2 -> sound adress
 * 5 -> partie 1
 * 11 -> adress partie courante
 * 
 * 
 * -1 veut dire pas de partie enregistrer
 */
/* reset EEPROM Pin */
byte resetStagePin = 22;

/* EEPROM Variable */

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
void doPlayMenu(uint8_t selected);
void doStatsMenu(uint8_t selected);
void doOptionsMenu(uint8_t selected);

static const char* mainMenuItems[] = { "Play", "Stats","Options"};
static const XMenu mainMenu = {
  "Principal",
  mainMenuItems,
  3,
  &doMainMenu
};
static const char* playMenuItems[] = { "Jouer", "Recommencer", "Cheat"};
static const XMenu playMenu = {
  "Jouer",
  playMenuItems,
  3,
  &doPlayMenu
};
static const char* statsMenuItems[] = { "Progression", "Best progression", "Nombre demarrage"};
static const XMenu statsMenu = {
  "Statistiques",
  statsMenuItems,
  3,
  &doStatsMenu
};
static const char* optionsMenuItems[] = { "Audio", "Reset all"};
static const XMenu optionsMenu = {
  "Options",
  optionsMenuItems,
  2,
  &doOptionsMenu
};

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
void doMenu(XMenu menu) {
  XButtonId button;
  bool keephere = true;
  Serial.print("Welcome in the menu :");
  Serial.println(menu.title);
  Serial.println("===========================");
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
        Serial.println("++");
        choice++;
      break;
      case BT_DOWN:
        Serial.println("--");
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
  
  
  switch(selected){
    case 1://playmenu
      doMenu(playMenu);
      break;
    case 2:
      doMenu(statsMenu);
      break;
    case 3:
      doMenu(optionsMenu);
      break;
  }  
}
void doPlayMenu(uint8_t selected){
    
}
void doStatsMenu(uint8_t selected){
    return;
}
void doOptionsMenu(uint8_t selected){
    
}


