// --- MOTOR + ULTRASONIC TEST (WITH SERIAL MONITOR) ----

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

// ---- ULTRASONIC PINS ----
#define TRIG_PIN 2
#define ECHO_FRONT A5
#define ECHO_BACK 8
#define ECHO_LEFT 3
#define ECHO_RIGHT 9
#define DIST_THRESHOLD 40   // cm

// --- FUNCTIONS ---
long readDistance(int echoPin) {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  long duration = pulseIn(echoPin, HIGH, 30000);  // 30ms timeout
  long distance = duration * 0.0343 / 2;
  return distance;
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

void turnLeft(int speed) {
  analogWrite(LEFT_RPWM, 0);
  analogWrite(LEFT_LPWM, speed);
  analogWrite(RIGHT_RPWM, speed);
  analogWrite(RIGHT_LPWM, 0);
}

void turnRight(int speed) {
  analogWrite(LEFT_RPWM, speed);
  analogWrite(LEFT_LPWM, 0);
  analogWrite(RIGHT_RPWM, 0);
  analogWrite(RIGHT_LPWM, speed);
}

void stopMotors() {
  analogWrite(LEFT_RPWM, 0);
  analogWrite(LEFT_LPWM, 0);
  analogWrite(RIGHT_RPWM, 0);
  analogWrite(RIGHT_LPWM, 0);
}

void setup() {
  // --- Motor Setup ---
  pinMode(LEFT_RPWM, OUTPUT);
  pinMode(LEFT_LPWM, OUTPUT);
  pinMode(LEFT_REN, OUTPUT);
  pinMode(LEFT_LEN, OUTPUT);
  pinMode(RIGHT_RPWM, OUTPUT);
  pinMode(RIGHT_LPWM, OUTPUT);
  pinMode(RIGHT_REN, OUTPUT);
  pinMode(RIGHT_LEN, OUTPUT);

  digitalWrite(LEFT_REN, HIGH);
  digitalWrite(LEFT_LEN, HIGH);
  digitalWrite(RIGHT_REN, HIGH);
  digitalWrite(RIGHT_LEN, HIGH);

  // --- Ultrasonic Setup ---
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_FRONT, INPUT);
  pinMode(ECHO_BACK, INPUT);
  pinMode(ECHO_LEFT, INPUT);
  pinMode(ECHO_RIGHT, INPUT);

  // --- Serial Monitor ---
  Serial.begin(9600);
  Serial.println("=== AGV Ultrasonic + Motor Test ===");
}

void loop() {
  long front = readDistance(ECHO_FRONT);
  long back  = readDistance(ECHO_BACK);
  long left  = readDistance(ECHO_LEFT);
  long right = readDistance(ECHO_RIGHT);

  // --- Print distances to Serial Monitor ---
  Serial.print("Front: "); Serial.print(front); Serial.print(" cm | ");
  Serial.print("Back: ");  Serial.print(back);  Serial.print(" cm | ");
  Serial.print("Left: ");  Serial.print(left);  Serial.print(" cm | ");
  Serial.print("Right: "); Serial.print(right); Serial.println(" cm");


  delay(200);
}