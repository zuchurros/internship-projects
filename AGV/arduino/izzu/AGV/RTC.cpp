#include "RTC.h"
// 9,2,5
RTC_DS3231 rtc;

void setupRTC() {
  Wire.begin();

  if (!rtc.begin()) {
    Serial.println("Couldn't find RTC module!");
    while (1);
  }

  if (rtc.lostPower()) {
    Serial.println("RTC lost power, setting to compile time...");
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }
}

String getFormattedTime() {
  DateTime now = rtc.now();
  char buffer[9];
  sprintf(buffer, "%02d:%02d:%02d", now.hour(), now.minute(), now.second());
  return String(buffer);
}

String getFormattedDate() {
  DateTime now = rtc.now();
  char buffer[11];
  sprintf(buffer, "%02d/%02d/%04d", now.day(), now.month(), now.year());
  return String(buffer);
}

// Combined function for date + time
String getDateTimeString() {
  DateTime now = rtc.now();
  char buffer[20];
  sprintf(buffer, "%04d-%02d-%02d %02d:%02d:%02d",
          now.year(), now.month(), now.day(),
          now.hour(), now.minute(), now.second());
  return String(buffer);
}