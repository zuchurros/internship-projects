#include <Wire.h>
#include <PCF8574.h>
#include <LiquidCrystal_I2C.h>
#include "Navigation.h"
#include "Sensors.h"

// === Objects ===
PCF8574 pcf8574(0x20);
LiquidCrystal_I2C lcd(0x27, 20, 4);

void setup() {
  Serial.begin(9600);
  Wire.begin();
  lcd.init();
  lcd.backlight();

  pcf8574.begin();
  setupMotors();
  setupSensors();

  lcd.setCursor(0, 0);
  lcd.print("AGV Initialized");
  delay(1000);
  lcd.clear();
}

void loop() {
  if (checkObstacle()) {
    stopMotors();
    lcd.println("Obstacle detected - Stopped");
    delay(100);
    return;
  }

  followLinePID();
  
}