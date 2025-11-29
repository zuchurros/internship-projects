#ifndef MOTORS_H
#define MOTORS_H

#include <Arduino.h>

void setupMotors();
void setMotorSpeed(int leftSpeed, int rightSpeed); // -255..+255
void stopMotors();
void moveForward(int speed);   // convenience
void moveBackward(int speed);  // convenience
void turnLeft(int speed);
void turnRight(int speed);

#endif // MOTORS_H