#include "Navigation.h"
#include "Sensors.h"
#include <Arduino.h>

// === Motor Pins ===
#define L_RPWM 10
#define L_LPWM 11
#define L_EN_L 7
#define L_EN_R 4
#define R_RPWM 5
#define R_LPWM 6
#define R_EN_L 13
#define R_EN_R 12

// === PID Parameters ===
float Kp = 25.0;
float Ki = 0.0;
float Kd = 15.0;

float error = 0, lastError = 0;
float integral = 0;
float lastValidError = 0;   // For line recovery

int baseSpeed = 100;
int maxSpeed = 255;

void setupMotors() {
  pinMode(L_RPWM, OUTPUT);
  pinMode(L_LPWM, OUTPUT);
  pinMode(R_RPWM, OUTPUT);
  pinMode(R_LPWM, OUTPUT);

  pinMode(L_EN_L, OUTPUT);
  pinMode(L_EN_R, OUTPUT);
  pinMode(R_EN_L, OUTPUT);
  pinMode(R_EN_R, OUTPUT);

  digitalWrite(L_EN_L, HIGH);
  digitalWrite(L_EN_R, HIGH);
  digitalWrite(R_EN_L, HIGH);
  digitalWrite(R_EN_R, HIGH);

  stopMotors();
}

void setMotorSpeed(int leftSpeed, int rightSpeed) {
  leftSpeed  = constrain(leftSpeed,  0, maxSpeed);
  rightSpeed = constrain(rightSpeed, 0, maxSpeed);

  analogWrite(L_RPWM, leftSpeed);
  analogWrite(L_LPWM, 0);
  analogWrite(R_RPWM, rightSpeed);
  analogWrite(R_LPWM, 0);
}

void stopMotors() {
  analogWrite(L_RPWM, 0);
  analogWrite(L_LPWM, 0);
  analogWrite(R_RPWM, 0);
  analogWrite(R_LPWM, 0);
}

void followLinePID() { //untuk smooth cornering and line recovering, incase only straight line movement boleh ubah to a simpler one
  float newError = getLineError();

  // === Line recovery ===
  if (isnan(newError)) { // All sensors lost the line
    Serial.println("Line lost! Recovering...");
    // Continue turning slightly toward the last valid error direction
    if (lastValidError > 0) {
      setMotorSpeed(baseSpeed - 80, baseSpeed + 80); // Turn right
    } else {
      setMotorSpeed(baseSpeed + 80, baseSpeed - 80); // Turn left
    }
    delay(50);
    return;
  }

  // === Normal line following ===
  error = newError;
  integral += error;
  float derivative = error - lastError;
  float correction = (Kp * error) + (Ki * integral) + (Kd * derivative);
  lastError = error;
  lastValidError = error; // Store last valid error

int leftSpeed  = constrain(baseSpeed - correction, -255, 255);
int rightSpeed = constrain(baseSpeed + correction, -255, 255);

// optional: invert correction direction if turning feels reversed
// correction = -correction;
  setMotorSpeed(leftSpeed, rightSpeed);

  // === Debug output ===
  Serial.print("Error: ");
  Serial.print(error);
  Serial.print("\tCorrection: ");
  Serial.print(correction);
  Serial.print("\tL: ");
  Serial.print(leftSpeed);
  Serial.print("\tR: ");
  Serial.println(rightSpeed);

  delay(30);
}