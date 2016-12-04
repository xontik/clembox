#ifndef GLOBALS_H
#define GLOBALS_H
#include "notes.h"
#include "Arduino.h"
#include <LiquidCrystal_I2C.h> 

#define WIN 3
#define START 1

#define ARROW_UP 2
#define ARROW_DOWN 3
#define ARROW_LEFT 1
#define ARROW_RIGHT 0

/* input Pins */
extern byte lightSensorPin;

/* output Pins */
extern byte piezoMelodyPin;
extern byte relayOpenPin;
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
extern byte resetStagePin;

/* EEPROM Variable */

extern int stageAdress;
extern int soundAdress;
extern byte tmpStageValue;
extern byte stageValue;
extern bool stayInThisStage;
/* buttons */

/* Custom char*/
extern byte rightArrow[];
extern byte leftArrow[] ;
extern byte upArrow[];
extern byte downArrow[];
/* Melodys */
extern int sucessStageMel[];
extern int sucessStageDuration[];
extern int startMel[];
extern int startDuration[];
extern int melody[];
extern int dur[];

/* XMenu init*/
extern void doMainMenu(uint8_t selected);
extern void doPlayMenu(uint8_t selected);
extern void doStatsMenu(uint8_t selected);
extern void doOptionsMenu(uint8_t selected);






extern LiquidCrystal_I2C lcd; 
#endif

