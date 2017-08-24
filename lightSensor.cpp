#include "Arduino.h"
#include "lightSensor.h"

int getLight(int pin){
  int v = analogRead(pin);
  Serial.print("Light Sensor value:");
  Serial.println(v);
  if(v < 3){
    return NO_LIGHT;
  }
  if(v < 6){
    return LOW_LIGHT;
  }
  if(v < 100){
    return HIGH_LIGHT;
  }
  return FULL_LIGHT;
}

