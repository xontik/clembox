#include "XMenu.h"

void displayMenu(XMenu menu){
    int i;
    Serial.println(menu.title);
    for(i=0;i<menu.nbItems;i++){
      Serial.println(menu.items[i]);
    }

    
}



