#include <Servo.h>

Servo horizontal; // horizontal servo
int servoh = 180;
int servohLimitHigh = 175;
int servohLimitLow = 5;

Servo vertical; // vertical servo
int servov = 45;
int servovLimitHigh = 100;
int servovLimitLow = 1;

// LDR pin connections
int ldrtl = A0; // LDR top left - BOTTOM LEFT
int ldrrt = A3; // LDR top right - BOTTOM RIGHT
int ldrml = A1; // LDR mid left - TOP LEFT
int ldrrl = A2; // LDR mid right - TOP RIGHT
int ldrbl = A4; // LDR bottom left
int ldrbm = A5; // LDR bottom mid
int ldrtm = A6; // LDR top mid
int ldrtr = A7; // LDR top right
int ldrc = A8;  // LDR center - CENTER

void setup() {
  horizontal.attach(9);
  vertical.attach(10);
  horizontal.write(180);
  vertical.write(45);
  delay(2500);
}

void loop() {
  int lt = analogRead(ldrtl); // LDR top left - BOTTOM LEFT
  int rt = analogRead(ldrrt); // LDR top right - BOTTOM RIGHT
  int ml = analogRead(ldrml); // LDR mid left - TOP LEFT
  int mr = analogRead(ldrrl); // LDR mid right - TOP RIGHT
  int bl = analogRead(ldrbl); // LDR bottom left
  int bm = analogRead(ldrbm); // LDR bottom mid
  int tm = analogRead(ldrtm); // LDR top mid
  int tr = analogRead(ldrtr); // LDR top right
  int c = analogRead(ldrc); // LDR center - CENTER

  // Calculate average values
  int avt = (lt + rt + tm + tr) / 4; // average value top
  int avd = (bl + bm + ml + mr) / 4; // average value down
  int avl = (lt + ml + bl) / 3; // average value left
  int avr = (rt + mr + tr) / 3; // average value right
  int avc = c; // average value center

  int dtime = 10;
  int tol = 90;

  int dvert = avt - avd; // check the difference of up and down
  int dhoriz = avl - avr; // check the difference of left and right


  if (-1 * tol > dvert || dvert > tol) {
    if (avt > avd) {
      servov = ++servov;
      if (servov > servovLimitHigh) {
        servov = servovLimitHigh;
      }
    } else if (avt < avd) {
      servov = --servov;
      if (servov < servovLimitLow) {
        servov = servovLimitLow;
      }
    }
    vertical.write(servov);
  }

  if (-1 * tol > dhoriz || dhoriz > tol) {
    if (avl > avr) {
      servoh = --servoh;
      if (servoh < servohLimitLow) {
        servoh = servohLimitLow;
      }
    } else if (avl < avr) {
      servoh = ++servoh;
      if (servoh > servohLimitHigh) {
        servoh = servohLimitHigh;
      }
    }
    horizontal.write(servoh);
      Serial.print( servoh);
  Serial.print( servov);
  }

  delay(dtime);
}
