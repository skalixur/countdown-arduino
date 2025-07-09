// Set the date to count down to below, as a Unix timestamp, from now to sometime before the year ~2106
// Unix timestamps need to be adjusted to your timezone if the RTC module is calibrated to local time
// ex: GMT+8 should add (60 * 60) * 8 to the unix timestamp
uint32_t countdownDate = 1800000000;

// Messages line 1 and 2. On an LCD-1602A, max 14 characters per line. Both displayed every four seconds.
String message1 = "Even monkeys";
String message2 = "fall from trees";