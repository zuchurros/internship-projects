// --- FULL INTEGRATED TEST ---

// Motor pins
#define EN_L 4
#define L_PWM 5
#define L_DIR 6
#define EN_R 7
#define R_PWM 10
#define R_DIR 11

// Ultrasonic
#define TRIG_PIN 2
#define ECHO_FRONT A0
#define ECHO_LEFT A1
#define ECHO_RIGHT A2
#define ECHO_BACK A3
#define DIST_THRESHOLD 15

// Line sensors
#define IR1 A0
#define IR2 A1
#define IR3 A2
#define IR4 A3
#define IR5 8

int baseSpeed = 150;
int Kp = 25;

long readUltrasonic(int echoPin) {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  long duration = pulseIn(echoPin, HIGH, 25000);
  return duration * 0.034 / 2;
}

void setup() {
  Serial.begin(9600);

  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_FRONT, INPUT);
  pinMode(ECHO_LEFT, INPUT);
  pinMode(ECHO_RIGHT, INPUT);
  pinMode(ECHO_BACK, INPUT);

  pinMode(EN_L, OUTPUT);
  pinMode(EN_R, OUTPUT);
  digitalWrite(EN_L, HIGH);
  digitalWrite(EN_R, HIGH);

  pinMode(L_PWM, OUTPUT);
  pinMode(R_PWM, OUTPUT);
  pinMode(L_DIR, OUTPUT);
  pinMode(R_DIR, OUTPUT);

  pinMode(IR1, INPUT);
  pinMode(IR2, INPUT);
  pinMode(IR3, INPUT);
  pinMode(IR4, INPUT);
  pinMode(IR5, INPUT);

  Serial.println("Integrated Test Start");
}

void loop() {
  // Ultrasonic obstacle detection
  long front = readUltrasonic(ECHO_FRONT);
  if (front < DIST_THRESHOLD && front > 0) {
    analogWrite(L_PWM, 0);
    analogWrite(R_PWM, 0);
    Serial.println("Obstacle detected! Stopping...");
    delay(500);
    return;
  }

  // Line following
  int s1 = digitalRead(IR1);
  int s2 = digitalRead(IR2);
  int s3 = digitalRead(IR3);
  int s4 = digitalRead(IR4);
  int s5 = digitalRead(IR5);

  int position = (-2 * s1) - s2 + s4 + (2 * s5);
  int correction = Kp * position;

  int leftSpeed = constrain(baseSpeed - correction, 0, 255);
  int rightSpeed = constrain(baseSpeed + correction, 0, 255);

  digitalWrite(L_DIR, HIGH);
  digitalWrite(R_DIR, HIGH);
  analogWrite(L_PWM, leftSpeed);
  analogWrite(R_PWM, rightSpeed);

  delay(50);
}