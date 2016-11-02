#ifndef XMENU_H
#define XMENU_H
#include <Arduino.h>

/* XMenu def */
typedef struct{
  const char* title;
  const char** items;
  const uint8_t nbItems;
  void (*calbackFct)(uint8_t);
} XMenu;

void displayMenu(XMenu m, int choice);

  

#endif
