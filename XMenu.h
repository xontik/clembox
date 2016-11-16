#ifndef XMENU_H
#define XMENU_H
#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include "XInput.h"

#define ARROW_UP 2
#define ARROW_DOWN 3
#define ARROW_LEFT 1
#define ARROW_RIGHT 0
/* XMenu def */
typedef struct{
  const char* title;
  const char** items;
  const uint8_t nbItems;
  void (*calbackFct)(uint8_t);
} XMenu;


void displayMenu(XMenu m ,LiquidCrystal_I2C *lcd,int choice);
void displayMenuS(XMenu m, int choice);

  

#endif
