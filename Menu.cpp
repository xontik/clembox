#include "Menu.h"
#include "XInput.h"

const int nbMenuItems = 3;
const char* menuItems[] = {"Jouer", "Reset","Statistiques"};

void displayMenu(int choice){
    lcd.clear();
    lcd.print("Menu Principal ");
    lcd.setCursor(1,1);
    lcd.print(menuItems[0]);
    lcd.setCursor(1,2);
    lcd.print(menuItems[1]);
    lcd.setCursor(1,3);
    lcd.print(menuItems[2]);
    lcd.setCursor(0,choice);
    lcd.write(ARROW_RIGHT);

}
void doMainMenu(int choice){
  switch(choice){
    case 1:
      void doPlay();
      break;
    case 2:
      void doReset();
      break;
    case 3:
      void doToggleAudio();
      break;
    case 4:
      void doStats();
      break;
  }
}
void mainMenu(){
  int choice = 1;
  XButtonId button;
  bool keephere = true;
  while(keephere){
    displayMenu(choice);
    // Wait relache boutons 
    button = input.buttonPushed();
    //gestions des differents cas
    switch(button){
      case BT_UP:
        choice++;
      break;
      case BT_DOWN:
        choice--;
      break;
      case BT_LEFT:
        keephere = false;
      break;
      case BT_RIGHT:
      case BT_VALID:
        doMainMenu(choice);
      break;
    }
    if(choice > nbMenuItems){
      choice = 1;
    }
    if(choice < 1){
      choice = nbMenuItems;
    }
  }
}

void doPlay(){
  
}
void doStats(){
  
}
void doReset(){
  
}
void doToggleAudio(){

}

