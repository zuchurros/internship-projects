#include "Sensors.h"

#define TRIG_FRONT 2
#define ECHO_FRONT A5
#define TRIG_LEFT 3
#define ECHO_LEFT 8
#define TRIG_RIGHT 4
#define ECHO_RIGHT 9

#define DIST_THRESHOLD 25

void setupSensors() {
  pinMode(TRIG_FRONT, OUTPUT);
  pinMode(ECHO_FRONT, INPUT_PULLUP);
  pinMode(TRIG_LEFT, OUTPUT);
  pinMode(ECHO_LEFT, INPUT_PULLUP);
  pinMode(TRIG_RIGHT, OUTPUT);
  pinMode(ECHO_RIGHT, INPUT_PULLUP);
}

long readUltrasonic(int trigPin, int echoPin) {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  long duration = pulseIn(echoPin, HIGH, 20000); // timeout 20ms
  if (duration == 0) return -1;  // no echo received
  return duration * 0.034 / 2;   // distance in cm
}

bool checkObstacle() {
  long front = readUltrasonic(TRIG_FRONT, ECHO_FRONT);
  delay(10);
  long left = readUltrasonic(TRIG_LEFT, ECHO_LEFT);
  delay(10);
  long right = readUltrasonic(TRIG_RIGHT, ECHO_RIGHT);
  delay(10);

  // Only treat as obstacle if valid reading (< DIST_THRESHOLD)
  bool obstacleFront = (front > 0 && front < DIST_THRESHOLD);
  bool obstacleLeft  = (left  > 0 && left  < DIST_THRESHOLD);
  bool obstacleRight = (right > 0 && right < DIST_THRESHOLD);

  return (obstacleFront || obstacleLeft || obstacleRight);
}

float getLineError() {
  int s1 = pcf8574.digitalRead(0);
  int s2 = pcf8574.digitalRead(1);
  int s3 = pcf8574.digitalRead(2);
  int s4 = pcf8574.digitalRead(3);
  int s5 = pcf8574.digitalRead(4);

  Serial.print("IRs: ");
  Serial.print(s1); Serial.print(" ");
  Serial.print(s2); Serial.print(" ");
  Serial.print(s3); Serial.print(" ");
  Serial.print(s4); Serial.print(" ");
  Serial.println(s5);

  int error = 0;
  if (s1 == LOW) error = -2;
  else if (s2 == LOW) error = -1;
  else if (s3 == LOW) error = 0;
  else if (s4 == LOW) error = 1;
  else if (s5 == LOW) error = 2;

  return error;
}