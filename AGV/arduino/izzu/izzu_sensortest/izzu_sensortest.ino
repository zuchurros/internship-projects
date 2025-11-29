#include <Wire.h>
#include <Adafruit_PCF8574.h>

Adafruit_PCF8574 pcf;

void setup() {
  Serial.begin(115200);
  if (!pcf.begin(0x27, &Wire)) {
    Serial.println("Couldn't find PCF8574 at 0x27!");
    while (1);
  }
  Serial.println("PCF8574 detected at 0x27");

  // Set all pins as output for test
  for (uint8_t i = 0; i < 8; i++) {
    pcf.pinMode(i, OUTPUT);
  }
}

void loop() {
  for (uint8_t i = 0; i < 8; i++) {
    Serial.print("Toggling P");
    Serial.println(i);
    pcf.digitalWrite(i, HIGH);
    delay(300);
    pcf.digitalWrite(i, LOW);
    delay(300);
  }
  Serial.println("Cycle done.\n");
  delay(500);
}