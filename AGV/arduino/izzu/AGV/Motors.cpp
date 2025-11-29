#include "Motors.h"
#include "Definitions.h"
#include <Arduino.h>

void setupMotors() {
  // PWM pins
  pinMode(LEFT_RPWM, OUTPUT);
  pinMode(LEFT_LPWM, OUTPUT);
  pinMode(RIGHT_RPWM, OUTPUT);
  pinMode(RIGHT_LPWM, OUTPUT);

  // Enable pins
  pinMode(LEFT_EN, OUTPUT);
  pinMode(RIGHT_EN, OUTPUT);

  // Default disabled until explicitly enabled
  digitalWrite(LEFT_EN, LOW);
  digitalWrite(RIGHT_EN, LOW);

  // Ensure motors stopped
  analogWrite(LEFT_RPWM, 0);
  analogWrite(LEFT_LPWM, 0);
  analogWrite(RIGHT_RPWM, 0);
  analogWrite(RIGHT_LPWM, 0);
}

static inline void enableDrivers(bool enLeft=true, bool enRight=true) {
  digitalWrite(LEFT_EN, enLeft ? HIGH : LOW);
  digitalWrite(RIGHT_EN, enRight ? HIGH : LOW);
}

void setMotorSpeed(int leftSpeed, int rightSpeed) {
  // speed range -255..255
  leftSpeed = constrain(leftSpeed, -MOTOR_SPEED_MAX, MOTOR_SPEED_MAX);
  rightSpeed = constrain(rightSpeed, -MOTOR_SPEED_MAX, MOTOR_SPEED_MAX);

  // enable drivers (safe default)
  enableDrivers(true, true);

  // Left motor
  if (leftSpeed >= 0) {
    analogWrite(LEFT_RPWM, leftSpeed);
    analogWrite(LEFT_LPWM, 0);
  } else {
    analogWrite(LEFT_RPWM, 0);
    analogWrite(LEFT_LPWM, abs(leftSpeed));
  }

  // Right motor
  if (rightSpeed >= 0) {
    analogWrite(RIGHT_RPWM, rightSpeed);
    analogWrite(RIGHT_LPWM, 0);
  } else {
    analogWrite(RIGHT_RPWM, 0);
    analogWrite(RIGHT_LPWM, abs(rightSpeed));
  }
}

void stopMotors() {
  analogWrite(LEFT_RPWM, 0);
  analogWrite(LEFT_LPWM, 0);
  analogWrite(RIGHT_RPWM, 0);
  analogWrite(RIGHT_LPWM, 0);
}

void moveForward(int speed) {
  setMotorSpeed(speed, speed);
}

void moveBackward(int speed) {
  setMotorSpeed(-speed, -speed);
}

void turnLeft(int speed) {
  setMotorSpeed(-speed, speed);
}

void turnRight(int speed) {
  setMotorSpeed(speed, -speed);
}