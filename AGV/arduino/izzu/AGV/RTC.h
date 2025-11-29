#ifndef RTC_H
#define RTC_H

#include <RTClib.h>

extern RTC_DS3231 rtc;

// Initialization
void setupRTC();

// Getters
String getFormattedTime();
String getFormattedDate();
String getDateTimeString();  

#endif