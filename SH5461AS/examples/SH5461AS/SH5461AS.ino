/*#################################################################################
 * This library was produced by Halina
 * 
 *  github: https://github.com/halina20011/Arduino-SH5461AS-library
###################################################################################*/
#include "SH5461AS.h"

int digit1 = 6;
int digit2 = 9;
int digit3 = 10;
int digit4 = 11;

#define DISPLAY_BRIGHTNESS  200

int segA = 2;
int segB = 3;
int segC = 4;
int segD = 5;
int segE = A0;
int segF = 7;
int segG = 8;

int dp = 12;

SH5461AS sh = SH5461AS(digit1, digit2, digit3, digit4, segA, segB, segC, segD, segE, segF, segG, dp);

unsigned long previousMillis = 0;
const long interval = 500;

int i = 0;
//float x = 1.1;

void setup() {
  Serial.begin(9600);
}

void loop() {
  sh.showInt(i);
//  sh.showFloat(x)
//  sh.showTemperature(i);
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    i++;
//    x += 1.0;
  }
}
