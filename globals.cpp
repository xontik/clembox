#include "globals.h"
#include "Arduino.h"

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
/* buttons */
XButton buttons[] = {
  {24,BT_UP},
  {25,BT_DOWN},
  {23,BT_LEFT},
  {22,BT_RIGHT},
  {27,BT_VALID},
  {-1,BT_NONE}
  
  };
/* Custom char*/
byte rightArrow[] = {B00000,B00100,B00010,B11111,B00010,B00100,B00000};
byte leftArrow[] = {B00000,B00100,B01000,B11111,B01000,B00100,B00000};
byte upArrow[] = {B00100,B01110,B10101,B00100,B00100,B00100,B00000};
byte downArrow[] = {B00000,B00100,B00100,B00100,B10101,B01110,B00100};

/* Melodys */
int sucessStageMel[] = {NOTE_F4,NOTE_FS4,NOTE_G4,NOTE_GS4,NOTE_END};
int sucessStageDuration[] = {6, 6, 6, 2};
int startMel[] = {NOTE_C5,NOTE_END};
int startDuration[] = {1};
int melody[] = {NOTE_C4, NOTE_G3, NOTE_G3, NOTE_A3, NOTE_G3, 0, NOTE_B3, NOTE_C4};
int dur[] = {4, 8, 8, 4, 4, 4, 4, 4};


const char* mainMenuItems[] = { "Play", "Stats","Options"};
const XMenu mainMenu = {
  "Principal",
  mainMenuItems,
  3,
  &doMainMenu
};
const char* playMenuItems[] = { "Jouer", "Recommencer", "Cheat"};
const XMenu playMenu = {
  "Jouer",
  playMenuItems,
  3,
  &doPlayMenu
};
const char* statsMenuItems[] = { "Progression", "Best progression", "Nombre demarrage"};
const XMenu statsMenu = {
  "Statistiques",
  statsMenuItems,
  3,
  &doStatsMenu
};
const char* optionsMenuItems[] = { "Audio", "Reset all"};
const XMenu optionsMenu = {
  "Options",
  optionsMenuItems,
  2,
  &doOptionsMenu
};

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

