#ifndef SENSORS_H
#define SENSORS_H

#include <Arduino.h>
#include <PCF8574.h>

extern PCF8574 pcf8574;

void setupSensors();
float getLineError();
bool checkObstacle();

#endif