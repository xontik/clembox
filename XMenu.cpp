#include "XMenu.h"

void displayMenu(XMenu menu, int choice = 1){
    int i;
    Serial.println(menu.title);
    if(choice == 1){
        Serial.println(menu.items[menu.nbItems-1]);
        Serial.print("->");
        Serial.println(menu.items[0]);
        Serial.println(menu.items[1]);
    }else if(choice == menu.nbItems){
        Serial.println(menu.items[menu.nbItems-2]);
        Serial.print("->");
        Serial.println(menu.items[menu.nbItems-1]);
        Serial.println(menu.items[0]);
    }else{
        Serial.println(menu.items[choice-2]);
        Serial.print("->");
        Serial.println(menu.items[choice-1]);
        Serial.println(menu.items[choice]);
    }
}



