#include <DS3231.h>
#include <Wire.h>

RTClib rtc;

void setup() {
  // Start the serial port
  Serial.begin(57600);

  // Start the I2C interface
  Wire.begin();
}


String timeUntil(int dateAndTime) {
  // String dateAndTime: A date and time in the future as a Unix Timestamp
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
  Serial.println(timeUntil(1754496000));
  delay(1000);
}