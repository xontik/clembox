#ifndef LIGHT_SENSOR_H
#define LIGHT_SENSOR_H

#include "Arduino.h"
#include "globals.h"

#define NO_LIGHT 0
#define LOW_LIGHT 1
#define HIGH_LIGHT 2
#define FULL_LIGHT 3


int getLight(int pin);

#endif
