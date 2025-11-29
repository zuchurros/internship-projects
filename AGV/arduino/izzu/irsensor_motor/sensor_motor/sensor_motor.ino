// === IR & Motor Test Code ===
// For dual BTS7960 drivers + 5 IR sensors via PCF8574 I/O expander
// Includes smooth cornering control

#include <Wire.h>
#include <PCF8574.h>

// === I2C Expander Address ===
// Default address: 0x20 (A0–A2 → GND)
PCF8574 pcf8574(0x21);

// === IR Sensor Pins on Expander ===
#define IR1 0  // Leftmost
#define IR2 1
#define IR3 2  // Center
#define IR4 3
#define IR5 4  // Rightmost

// === Left Motor Pins ===
#define L_RPWM 5
#define L_LPWM 6
#define L_EN_L 7
#define L_EN_R 4

// === Right Motor Pins ===
#define R_RPWM 10
#define R_LPWM 11
#define R_EN_L 13
#define R_EN_R 12

// === Base Speeds ===
int baseSpeed = 40;     // Normal forward speed
int turnSpeed = 80;     // Inner wheel speed when cornering
int sharpTurnSpeed = 20; // For very tight corners

void setup() {
  Serial.begin(115200);

  Wire.begin();
  pcf8574.begin();

  // IR sensor pins as input
  pcf8574.pinMode(IR1, INPUT);
  pcf8574.pinMode(IR2, INPUT);
  pcf8574.pinMode(IR3, INPUT);
  pcf8574.pinMode(IR4, INPUT);
  pcf8574.pinMode(IR5, INPUT);

  // Motor pins
  pinMode(L_RPWM, OUTPUT);
  pinMode(L_LPWM, OUTPUT);
  pinMode(R_RPWM, OUTPUT);
  pinMode(R_LPWM, OUTPUT);

  // Enable pins
  pinMode(L_EN_L, OUTPUT);
  pinMode(L_EN_R, OUTPUT);
  pinMode(R_EN_L, OUTPUT);
  pinMode(R_EN_R, OUTPUT);

  // Enable motor drivers
  digitalWrite(L_EN_L, HIGH);
  digitalWrite(L_EN_R, HIGH);
  digitalWrite(R_EN_L, HIGH);
  digitalWrite(R_EN_R, HIGH);

  stopMotors();
  Serial.println("AGV ready!");
}

void loop() {

    byte error, address;
  int devices = 0;

  Serial.println("Scanning...");

  for (address = 1; address < 127; address++) {
    Wire.beginTransmission(address);
    error = Wire.endTransmission();

    if (error == 0) {
      Serial.print("✅ Device found at 0x");
      if (address < 16) Serial.print("0");
      Serial.print(address, HEX);
      Serial.println();

      devices++;
    } else if (error == 4) {
      Serial.print("⚠️ Unknown error at address 0x");
      if (address < 16) Serial.print("0");
      Serial.println(address, HEX);
    }
  }

  if (devices == 0)
    Serial.println("❌ No I2C devices found\n");
  else
    Serial.println("Scan complete\n");

  delay(5000);  // rescan every 5 seconds
  // Read IR sensors (LOW = line detected)
  int s1 = pcf8574.digitalRead(IR1);
  int s2 = pcf8574.digitalRead(IR2);
  int s3 = pcf8574.digitalRead(IR3);
  int s4 = pcf8574.digitalRead(IR4);
  int s5 = pcf8574.digitalRead(IR5);

  Serial.print("IR: ");
  Serial.print(s1); Serial.print(" ");
  Serial.print(s2); Serial.print(" ");
  Serial.print(s3); Serial.print(" ");
  Serial.print(s4); Serial.print(" ");
  Serial.println(s5);

  // ===== Line Following Logic =====
  if (s3 == LOW) {
    // Center sensor detects line → go straight
    moveForward(baseSpeed, baseSpeed);
  } 
  else if (s2 == LOW) {
    // Slight left correction
    moveForward(baseSpeed, turnSpeed);
  } 
  else if (s4 == LOW) {
    // Slight right correction
    moveForward(turnSpeed, baseSpeed);
  } 
  else if (s1 == LOW) {
    // Hard left corner
    moveForward(baseSpeed, sharpTurnSpeed);
  } 
  else if (s5 == LOW) {
    // Hard right corner
    moveForward(sharpTurnSpeed, baseSpeed);
  } 
  else {
    // Lost line → stop
    stopMotors();
  }

  delay(20);
}

// === Motor Control Functions ===
void moveForward(int leftSpeed, int rightSpeed) {
  // Left motor forward
  analogWrite(L_RPWM, leftSpeed);
  analogWrite(L_LPWM, 0);
  // Right motor forward
  analogWrite(R_RPWM, rightSpeed);
  analogWrite(R_LPWM, 0);
}

void stopMotors() {
  analogWrite(L_RPWM, 0);
  analogWrite(L_LPWM, 0);
  analogWrite(R_RPWM, 0);
  analogWrite(R_LPWM, 0);
}