// ================================
//   Dual BTS7960 Motor Test (with Enable pins)
// ================================

// ---- LEFT MOTOR DRIVER PINS ----
#define LEFT_RPWM 5
#define LEFT_LPWM 6
#define LEFT_REN 4
#define LEFT_LEN 7

// ---- RIGHT MOTOR DRIVER PINS ----
#define RIGHT_RPWM 10
#define RIGHT_LPWM 11
#define RIGHT_REN 12
#define RIGHT_LEN 13

// ---- TEST PARAMETERS ----
#define MAX_PWM 160     // limit for safe speed
#define STEP_DELAY 100  // delay between PWM increments (ms)
#define HOLD_TIME 300000  // hold at full speed (ms)

void setup() {
  Serial.begin(9600);
  Serial.println("=== Dual Motor Test Start ===");

  // Set pin modes
  pinMode(LEFT_RPWM, OUTPUT);
  pinMode(LEFT_LPWM, OUTPUT);
  pinMode(LEFT_REN, OUTPUT);
  pinMode(LEFT_LEN, OUTPUT);

  pinMode(RIGHT_RPWM, OUTPUT);
  pinMode(RIGHT_LPWM, OUTPUT);
  pinMode(RIGHT_REN, OUTPUT);
  pinMode(RIGHT_LEN, OUTPUT);

  enableMotors();
  stopMotors();
  delay(1000);
}

void loop() {
  // Forward test
  moveBackward(200);
  delay(2000);
  stopMotors();
  delay(500);
  moveForward(200);
  delay(2000);

}

// ----------------------------
// Helper functions
// ----------------------------

void enableMotors() {
  digitalWrite(LEFT_REN, HIGH);
  digitalWrite(LEFT_LEN, HIGH);
  digitalWrite(RIGHT_REN, HIGH);
  digitalWrite(RIGHT_LEN, HIGH);
}

void moveForward(int speed) {
  analogWrite(LEFT_RPWM, speed);
  analogWrite(LEFT_LPWM, 0);
  analogWrite(RIGHT_RPWM, speed);
  analogWrite(RIGHT_LPWM, 0);
}

void moveBackward(int speed) {
  analogWrite(LEFT_RPWM, 0);
  analogWrite(LEFT_LPWM, speed);
  analogWrite(RIGHT_RPWM, 0);
  analogWrite(RIGHT_LPWM, speed);
}


void stopMotors() {
  analogWrite(LEFT_RPWM, 0);
  analogWrite(LEFT_LPWM, 0);
  analogWrite(RIGHT_RPWM, 0);
  analogWrite(RIGHT_LPWM, 0);
  Serial.println("Motors stopped");
}