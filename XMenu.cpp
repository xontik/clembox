#include "XMenu.h"
#include <LiquidCrystal_I2C.h> 
void displayMenu(XMenu menu, LiquidCrystal_I2C* lcd, int choice = 1){
    int i;
    displayMenuS(menu,choice);    
    lcd->clear();
    lcd->print("Menu : ");
    lcd->print(menu.title);
    
    if(menu.nbItems == 2){
        lcd->setCursor(0,choice);
        lcd->write(ARROW_RIGHT);
        lcd->setCursor(1,1);
        lcd->print(menu.items[0]);
        lcd->setCursor(1,2);
        lcd->print(menu.items[1]);  
      
    }else if(menu.nbItems > 3){
      if(choice == 1){
        lcd->setCursor(1,1);
        lcd->print(menu.items[menu.nbItems-1]);
        lcd->setCursor(0,2);
        lcd->write(ARROW_RIGHT);
        lcd->setCursor(1,2);
        lcd->print(menu.items[0]);
        lcd->setCursor(1,3);
        lcd->print(menu.items[1]);
    }else if(choice == menu.nbItems){
      lcd->setCursor(1,1);
        lcd->print(menu.items[menu.nbItems-2]);
        lcd->setCursor(0,2);
        lcd->write(ARROW_RIGHT);
        lcd->setCursor(1,2);
        lcd->print(menu.items[menu.nbItems-1]);
        lcd->setCursor(1,3);
        lcd->print(menu.items[0]);
    }else{
      lcd->setCursor(1,1);
        lcd->print(menu.items[choice-2]);
        lcd->setCursor(0,2);
        lcd->write(ARROW_RIGHT);
        lcd->setCursor(1,2);
        lcd->print(menu.items[choice-1]);
        lcd->setCursor(1,3);
        lcd->print(menu.items[choice]);
    }
   }else if(menu.nbItems == 3){
      
        lcd->setCursor(1,1);
        lcd->print(menu.items[0]);
        lcd->setCursor(1,2);
        lcd->print(menu.items[1]);
        lcd->setCursor(1,3);
        lcd->print(menu.items[2]);
        lcd->setCursor(0,choice);
        lcd->write(ARROW_RIGHT);
    }
   
    
}

void displayMenuS(XMenu menu, int choice = 1){
    int i;
    
    Serial.println(menu.title);
    if(menu.nbItems == 2){
       
        Serial.println(menu.items[choice]);
        Serial.print("->");
        Serial.println(menu.items[1-choice]);  
      
    }else{
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
    
}




