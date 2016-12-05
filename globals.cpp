#include "globals.h"
#include "Arduino.h"

/* input Pins */
byte lightSensorPin = A1;

/* output Pins */
byte piezoMelodyPin = 48;
byte relayOpenPin = 2;
/* EEPROM */
/*
 * 2 -> sound adress
 * 5 -> partie 1
 * 11 -> adress partie courante
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


LiquidCrystal_I2C lcd(0x27,20,4); 
/* Custom char*/
byte rightArrow[] = {B00000,B00100,B00010,B11111,B00010,B00100,B00000,B00000};
byte leftArrow[] = {B00000,B00100,B01000,B11111,B01000,B00100,B00000,B00000};
byte upArrow[] = {B00100,B01110,B10101,B00100,B00100,B00100,B00000,B00000};
byte downArrow[] = {B00000,B00100,B00100,B00100,B10101,B01110,B00100,B00000};

/* Melodys */
int sucessStageMel[] = {NOTE_F4,NOTE_FS4,NOTE_G4,NOTE_GS4,NOTE_END};
int sucessStageDuration[] = {6, 6, 6, 2};
int startMel[] = {NOTE_C5,NOTE_END};
int startDuration[] = {1};
int melody[] = {NOTE_C4, NOTE_G3, NOTE_G3, NOTE_A3, NOTE_G3, 0, NOTE_B3, NOTE_C4};
int dur[] = {4, 8, 8, 4, 4, 4, 4, 4};




