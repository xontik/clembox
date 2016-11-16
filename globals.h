#ifndef GLOBALS_H
#define GLOBALS_H
#include "Melody.h"
#include "Arduino.h"
#include "XMenu.h"
#include "XInput.h"
#include <LiquidCrystal_I2C.h> 
/* input Pins */
extern byte lightSensorPin;

/* output Pins */
extern byte piezoMelodyPin;
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
extern XButton buttons[];
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

extern const char* mainMenuItems[];
extern const XMenu mainMenu;
extern const char* playMenuItems[];
extern const XMenu playMenu;
extern const char* statsMenuItems[];
extern const XMenu statsMenu;
extern const char* optionsMenuItems[];
extern const XMenu optionsMenu;

extern void doMenu(XMenu menu);
#endif

