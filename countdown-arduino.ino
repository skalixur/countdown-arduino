#include <DS3231.h>
#include <Wire.h>
#include "config.h"
#include "LiquidCrystal_I2C.h"

const uint32_t secondsInYear = 60UL * 60 * 24 * 365;
const uint32_t secondsInDay = 60UL * 60 * 24;
const uint16_t secondsInHour = 60 * 60;
const byte secondsInMinute = 60;

RTClib rtc;

LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  lcd.init();
  lcd.backlight();

  lcd.setCursor(1, 0);
  lcd.print("Initializing..");
  Serial.begin(115200);

  Wire.begin();
}

void shift(String arr[], int& length) {
  for (int i = 1; i < length; i++) arr[i - 1] = arr[i];
  length--;
};

String pluralize(uint32_t count, String counter) {
  // return String(String(count) + ' ' + counter + (count == 1 ? "" : "s"));
  // Use shorthand dates instead to save space on the LCD
  String valueString = String(count);
  valueString = (valueString.length() < 2 ? "0" : "") + valueString;
  return String(valueString + counter[0]);
}

String dateArrayToString(String dateArray[], int length) {
  // while (dateArray[0].startsWith("0")) {
  //   shift(dateArray, length);
  // }

  String dateString;

  for (int i = 0; i < length; i++) {
    dateString += dateArray[i];
    if (i == length - 1) continue;
    dateString += " ";
  }

  return dateString;
}

String timeUntil(uint32_t dateAndTime) {
  // String dateAndTime: A date and time in the future as a Unix Timestamp, until the year ~2106
  // Example: 1752082329
  DateTime now = rtc.now();
  uint32_t then = dateAndTime;

  int32_t diff = (int32_t)(dateAndTime - now.unixtime());

  if (diff <= 0) {
    return "EVENT COMPLETE";
  }

  uint32_t duration = (uint32_t)diff;

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

void tick() {
  lcd.setCursor(0, 0);
  lcd.print("<");
}

void tock() {
  lcd.setCursor(0, 1);
  lcd.print(">");
}

void showCountdown() {
  String dateString = timeUntil(countdownDate);

  int dLocation = dateString.indexOf("d") + 1;

  String firstHalf = dateString.substring(0, dLocation);
  String secondHalf = dateString.substring(dLocation, dateString.length());
  secondHalf.trim();

  lcd.setCursor(5, 0);
  lcd.print(firstHalf);
  lcd.setCursor(3, 1);
  lcd.print(secondHalf);
}

int loopCount = 0;
bool showMessage = false;

void loop() {
  lcd.clear();
  if (loopCount == 1) {
    tick();
  } else if (loopCount == 2) {
    tick();
    tock();
  } else if (loopCount == 3) {
    tock();
  } else if (loopCount == 4) {
    loopCount = 0;
    showMessage ^= 1;
  }

  if (showMessage) {
    lcd.setCursor(2, 0);
    lcd.print(message1);
    lcd.setCursor(2, 1);
    lcd.print(message2);
  } else {
    showCountdown();
  }

  delay(1500);
  loopCount += 1;
}