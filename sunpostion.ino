#include <Wire.h>
#include <RTClib.h>
#include <SunPosition.h>
#include <Servo.h>

RTC_DS1307 rtc;
Servo motor1;
Servo motor2;

void setup() {
  Serial.begin(9600);
  Wire.begin();
  rtc.begin();
  motor1.attach(9); // Attach motor 1 to pin 9
  motor2.attach(10); // Attach motor 2 to pin 10

  // Set the initial date and time to May 7, 2024, 22:30:00
  DateTime initialTime(2024, 5, 8, 8, 0, 0);
  rtc.adjust(initialTime);

  Serial.println("RTC has been set to initial date and time.");
}

void loop() {
  // Get current time from RTC module
  DateTime now = rtc.now();

  // Calculate sun position
  SunPosition sunPos(33.82, 35.48, now.unixtime(),0); // Latitude, Longitude for Beirut, Lebanon
  float azimuth = sunPos.azimuth();
  float elevation = sunPos.altitude();

  // Display sun position
  Serial.print("Time: ");
  print2digits(now.hour());
  Serial.print(":");
  print2digits(now.minute());
  Serial.print(":");
  print2digits(now.second());
  Serial.print("  Azimuth: ");
  Serial.print(azimuth);
  Serial.print("  Elevation: ");
  Serial.println(elevation);

  // Control motors based on sun position
  // Example: Rotate motors based on azimuth value
  int motor1Angle = map(azimuth, 0, 360, 0, 180); // Map azimuth to servo angle
  int motor2Angle = map(elevation, -90, 90, 0, 180); // Map elevation to servo angle

  motor1.write(motor1Angle); // Set motor 1 angle
  motor2.write(motor2Angle); // Set motor 2 angle

  delay(1000); // Delay before updating again
}

void print2digits(int number) {
  if (number < 10) {
    Serial.print("0");
  }
  Serial.print(number);
}
