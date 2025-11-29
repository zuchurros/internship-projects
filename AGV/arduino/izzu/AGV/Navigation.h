#ifndef NAVIGATION_H
#define NAVIGATION_H

#include <Arduino.h>

void setupMotors();
void setMotorSpeed(int leftSpeed, int rightSpeed);
void stopMotors();
void followLinePID();

#endif