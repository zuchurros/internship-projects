#ifndef DEFINITIONS_H
#define DEFINITIONS_H

// ---------- Motor driver pins (BTS7960) ----------
#define LEFT_EN      4   // enable left driver (LEFT EN)
#define LEFT_RPWM    5   // PWM forward
#define LEFT_LPWM    6   // PWM reverse

#define RIGHT_EN     7   // enable right driver (RIGHT EN)
#define RIGHT_RPWM   10  // PWM forward
#define RIGHT_LPWM   11  // PWM reverse

// ---------- Ultrasonic (shared TRIG) ----------
#define US_TRIG      2
#define US_ECHO_F    A0
#define US_ECHO_B    A1
#define US_ECHO_L    A2
#define US_ECHO_R    A3

// ---------- Dock button ----------
#define DOCK_BUTTON  3   // toggle dock / undock

// ---------- I2C expander (PCF8574) ----------
#define PCF8574_ADDR 0x20

// PCF8574 pin mapping for 5-channel line sensor
#define EXP_IR1      0   // P0
#define EXP_IR2      1   // P1
#define EXP_IR3      2   // P2
#define EXP_IR4      3   // P3
#define EXP_IR5      4   // P4

// Other expander pins available: P5..P7

// ---------- Control constants ----------
#define MOTOR_SPEED_MAX 255
#define MOTOR_BASE_SPEED 150

#define ULTRASONIC_TIMEOUT_US 30000UL
#define ULTRASONIC_SETTLE_MS 60

// distance thresholds (cm)
#define OBSTACLE_THRESHOLD_CM 15
#define FRONT_ARRIVAL_CM 10

// PID (simple starting values, tune later)
#define KP 20.0f
#define KI 0.0f
#define KD 5.0f

#endif // DEFINITIONS_H