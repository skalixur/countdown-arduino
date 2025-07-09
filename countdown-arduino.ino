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

const uint32_t secondsInYear = 60UL * 60 * 24 * 365;
const uint32_t secondsInDay = 60UL * 60 * 24;
const uint16_t secondsInHour = 60 * 60;
const byte secondsInMinute = 60;

String timeUntil(uint32_t dateAndTime) {
  // String dateAndTime: A date and time in the future as a Unix Timestamp, until the year ~2106
  // Example: 1752082329
  DateTime now = rtc.now();
  DateTime then = DateTime(dateAndTime);

  if ((then.unixtime() - now.unixtime()) <= 0) {
    return "EVENT COMPLETE";
  }

  uint32_t duration = then.unixtime() - now.unixtime();

  uint32_t yearsToThen = duration / secondsInYear;
  duration %= secondsInYear;

  uint16_t daysToThen = duration / secondsInDay;
  duration %= secondsInDay;

  byte hoursToThen = duration / secondsInHour;
  duration %= secondsInHour;

  byte minutesToThen = duration / secondsInMinute;
  byte secondsToThen = duration % secondsInMinute;

  String dateString =
    String(yearsToThen) + " years, " + String(daysToThen) + " days, " + String(hoursToThen) + " hours, " + String(minutesToThen) + " minutes, " + String(secondsToThen) + " seconds until event";

  return dateString;
}

void loop() {
  Serial.println(timeUntil(countdownDate));

  delay(1000);
}