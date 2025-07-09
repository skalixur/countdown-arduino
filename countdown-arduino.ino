#include <DS3231.h>
#include <Wire.h>
#include "config.h"

RTClib rtc;

void setup() {
  // Start the serial port
  Serial.begin(115200);

  // Start the I2C interface
  Wire.begin();
}

const uint32_t secondsInYear = 60UL * 60 * 24 * 365;
const uint32_t secondsInDay = 60UL * 60 * 24;
const uint16_t secondsInHour = 60 * 60;
const byte secondsInMinute = 60;

String pluralize(uint32_t count, String counter) {
  return String(String(count) + ' ' + counter + (count == 1 ? "" : "s"));
}

void shift(String arr[], int& length) {
  for (int i = 1; i < length; i++) arr[i - 1] = arr[i];
  length--;
}

String dateArrayToString(String dateArray[], int length) {
  while (dateArray[0].startsWith("0")) {
    shift(dateArray, length);
  }

  String dateString;

  for(int i = 0; i < length; i++) {
    dateString += dateArray[i];
    if(i == length - 1) continue;
    dateString += ", " ;
  }

  return dateString;
}

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

  int length = 5;
  String dateArray[length] = { pluralize(yearsToThen, "year"), pluralize(daysToThen, "day"), pluralize(hoursToThen, "hour"), pluralize(minutesToThen, "minute"), pluralize(secondsToThen, "second") };

  String dateString = dateArrayToString(dateArray, length);

  return dateString;
}

void loop() {
  Serial.println(timeUntil(countdownDate));
  // Serial.println("hello");

  delay(1000);
}