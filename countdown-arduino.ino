#include <DS3231.h>
#include <Wire.h>
#include "config.h"

RTClib rtc;

void setup() {
  // Start the serial port
  Serial.begin(57600);

  // Start the I2C interface
  Wire.begin();
}


String timeUntil(uint32_t dateAndTime) {
  // String dateAndTime: A date and time in the future as a Unix Timestamp, until the year ~2106
  // Example: 1752082329

  DateTime now = rtc.now();
  DateTime then = DateTime(dateAndTime);
  unsigned long durationUntilThen = then.unixtime() - now.unixtime();
  DateTime duration = DateTime(durationUntilThen);

  unsigned int yearsUntil = duration.year();
  unsigned int daysUntil = duration.day();
  byte hoursUntil = duration.hour();
  byte minutesUntil = duration.minute();
  byte secondsUntil = duration.second();

  String timeUntilString = "";

  return String(durationUntilThen);
}

void loop() {
  Serial.println(timeUntil(countdownDate));
  delay(1000);
}