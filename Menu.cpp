#include "Menu.h"
#include "XInput.h"
#include <EEPROM.h>
#include "stages.h"

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
  Serial.print("domainmenu avec choix : ");
  Serial.println(choice);
  switch(choice){
    case 1:
      doPlay();
      break;
    case 2:
      doReset();
      break;
    case 3:
      doToggleAudio();
      break;
    case 4:
      doStats();
      break;
  }
}
void mainMenu(){
  int choice = 1;
  XButtonId button;
  bool keephere = true;
  while(keephere){
    displayMenu(choice);
    
    button = input.buttonPushed();
    
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
  Serial.println("doPlay");

  while(1){
    tmpStageValue = EEPROM.read(stageAdress);
    if(stageValue < tmpStageValue ){
      stageValue = tmpStageValue;
    }else if (stageValue != tmpStageValue){
      EEPROM.write(stageAdress,stageValue);
    }
  
    Serial.print("Stage value : ");
    Serial.println(stageValue);
    
    /* on renvoie sur la fonction gerant l'etape courante */
  
    if(doStage(stageValue)){
      stageValue++;
      mel.playMelody(sucessStageMel,sucessStageDuration);
    }else{
      return;
    }
    
      lcd.clear();
      lcd.setCursor(7,0);
      lcd.print("Bravo !");
      lcd.setCursor(0,2);
      lcd.print("Enigme suivante ");
      delay(500);
      lcd.print(".");
      delay(500);
      lcd.print(".");
      delay(500);
      lcd.print(".");
      delay(500);
    
  }
  
}
void doStats(){
  
}
void doReset(){
    lcd.clear();
    lcd.print("Reseted !!");
    stageValue = START;
    EEPROM.write(stageAdress,stageValue);
    Serial.println("Stages Reseted");
    delay(1000);
  
}
void doToggleAudio(){

}

