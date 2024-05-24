#include <Servo.h>

Servo azimuthServo;  // create servo object to control the azimuth
Servo elevationServo; // create servo object to control the elevation

void setup() {
  Serial.begin(9600); // starts the serial communication
  azimuthServo.attach(9);  // attaches the servo on pin 9
  elevationServo.attach(10); // attaches the servo on pin 10
}

void loop() {
  if (Serial.available()) {
    String data = Serial.readStringUntil('\n'); // read the incoming data as string until newline

    int separatorIndex = data.indexOf(','); // find the index of the comma separator

    // extract the azimuth and elevation from the data string
    String azimuthStr = data.substring(0, separatorIndex);
    String elevationStr = data.substring(separatorIndex + 1);

    // convert the azimuth and elevation to integers
    int azimuth = azimuthStr.toInt();
    int elevation = elevationStr.toInt();

    // move the servos to the calculated positions
    azimuthServo.write(azimuth);
    elevationServo.write(elevation);
  }
}
