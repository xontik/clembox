#include "XMenu.h"

void displayMenu(XMenu menu, int choice = 1){
    int i;
    Serial.println(menu.title);
    if(choice == 1){
        Serial.println(menu.items[menu.nbItems]);
        Serial.println(menu.items[0]);
        Serial.println(menu.items[1]);
    }else if(choice == menu.nbItems){
        Serial.println(menu.items[menu.nbItems-1]);
        Serial.println(menu.items[menu.nbItems]);
        Serial.println(menu.items[0]);
    }else{
      for(i=choice-1;i<choice+2;i++){
        Serial.println(menu.items[i]);
      }
    }
    
    

    
}



