# Arduino-4-digit-7-segment-led-display-library
Arduino librari for 4 digit 7 segment led display.


import Library: <br>
``#include "SH5461AS.h"`` <br>

Functions: <br>
``SH5461AS name = SH5461AS(digit1, digit2, digit3, digit4, segA, segB, segC, segD, segE, segF, segG, dp);``<br>
``name.showInt(int);`` <br>
``name.showFloat(float);`` <br>
``name.showTemperature(int)`` <br>
