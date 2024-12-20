#include <DS3231.h>

DS3231 rtc;

void setup() {
  Serial.begin(9600);
  Wire.begin();

  for (int led = 2; led < 14; led++){
    pinMode(led, OUTPUT);
  }

}

void loop() {
  bool h12;
  bool hPM;

  // Get the current hour and minute
  byte hour = rtc.getHour(h12, hPM);
  byte minute = rtc.getMinute();

  // Ensure hour is in 12-hour format (if needed)
  if (hour > 12) {
    hour -= 12;
  } else if (hour == 0) {
    hour = 12; // Handle midnight as 12 AM
  }

  // Extract the digits of the minute
  byte firstDigit = minute / 10; // Tens place
  byte secondDigit = minute % 10; // Units place

  // Convert to strings
  String hourStr = String(hour);
  String firstDigitStr = String(firstDigit);
  String secondDigitStr = String(secondDigit);

  int hourDigitalWrite[12][4] = {
    {},
    {3},
    {2},
    {5},
    {4},
    {2, 3},
    {2, 5},
    {4, 5},
    {3, 4},
    {2, 3, 4},
    {2, 3, 5},
    {2, 4, 5}
  };

  int minuteTenDigitalWrite[12][4] = {
    {},
    {7},
    {6},
    {8},
    {9},
    {6, 7},
    {6, 8},
    {8, 9},
    {7, 9},
    {6, 7, 9},
    {6, 7, 8},
    {6, 8, 9}
  };

  int minuteOneDigitalWrite[12][4] = {
    {},
    {11},
    {10},
    {12},
    {13},
    {10, 11},
    {10, 12},
    {12, 13},
    {11, 13},
    {10, 11, 13},
    {10, 11, 12},
    {10, 12, 13}
  };

  switchOnLeds(hourDigitalWrite[hour], sizeof(hourDigitalWrite[hour]) / sizeof(hourDigitalWrite[hour][0]));
  switchOnLeds(minuteTenDigitalWrite[minuteTen], sizeof(minuteTenDigitalWrite[minuteTen]) / sizeof(minuteTenDigitalWrite[minuteTen][0]));
  switchOnLeds(minuteOneDigitalWrite[minuteOne], sizeof(minuteOneDigitalWrite[minuteOne]) / sizeof(minuteOneDigitalWrite[minuteOne][0]));
}

void switchOnLeds(const int *pins, size_t size) {
  for (int i = 2; i < 14; i++) {
    bool pinFound = false;

    for (size_t j = 0; j < size; j++) {
      if (pins[j] == i) {
        pinFound = true;
        break;
      }
    }
    if (pinFound) {
      digitalWrite(i, HIGH);
    } else {
      digitalWrite(i, LOW);
    }
  }
}
