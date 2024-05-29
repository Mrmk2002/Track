#include <Servo.h>

Servo horizontal; // horizontal servo
Servo vertical;   // vertical servo

int servoh = 90;
int servohLimitHigh = 175;
int servohLimitLow = 5;

int servov = 90;
int servovLimitHigh = 100;
int servovLimitLow = 1;

// LDR pin connections with classifications
int ldrTopLeft = A1;      // Top left
int ldrTopMid = A6;       // Top mid
int ldrTopRight = A2;     // Top right
int ldrMidLeft = A4;      // Mid left
int ldrCenter = A8;       // Center (Mid-Mid)
int ldrMidRight = A7;     // Mid right
int ldrBottomLeft = A0;   // Bottom left
int ldrBottomMid = A5;    // Bottom mid
int ldrBottomRight = A3;  // Bottom right

void setup() {
  horizontal.attach(9);
  vertical.attach(10);
  horizontal.write(servoh);
  vertical.write(servov);
  delay(2500); // Allow servos to reach initial position
}

void loop() {
  // Read LDR values
  int tl = analogRead(ldrTopLeft);     // Top left
  int tm = analogRead(ldrTopMid);      // Top mid
  int tr = analogRead(ldrTopRight);    // Top right
  int ml = analogRead(ldrMidLeft);     // Mid left
  int c = analogRead(ldrCenter);       // Center (Mid-Mid)
  int mr = analogRead(ldrMidRight);    // Mid right
  int bl = analogRead(ldrBottomLeft);  // Bottom left
  int bm = analogRead(ldrBottomMid);   // Bottom mid
  int br = analogRead(ldrBottomRight); // Bottom right

  int maxTop = max(tl, max(tm, tr));   // Maximum value from the top row
  int maxBottom = max(bl, max(bm, br));// Maximum value from the bottom row
  int maxLeft = max(tl, max(ml, bl));  // Maximum value from the left column
  int maxRight = max(tr, max(mr, br)); // Maximum value from the right column

  int dtime = 10; // Delay time between adjustments

  // Vertical adjustment
  if (maxTop > maxBottom) {
    if (servov > servovLimitLow) {
      servov--;
    }
  } else {
    if (servov < servovLimitHigh) {
      servov++;
    }
  }
  vertical.write(servov); // Move vertical servo

  // Horizontal adjustment
  if (maxLeft > maxRight) {
    if (servoh > servohLimitLow) {
      servoh--;
    }
  } else {
    if (servoh < servohLimitHigh) {
      servoh++;
    }
  }
  horizontal.write(servoh); // Move horizontal servo

  delay(dtime); // Small delay for stability
}
