/*#################################################################################
 * This library was produced by Halina
 * 
 *  github: https://github.com/halina20011/Arduino-SH5461AS-library
###################################################################################*/
#include "Arduino.h"

class SH5461AS{
    public:
        SH5461AS(int digit1, int digit2, int digit3, int digit4, int segA, int segB, int segC, int segD, int segE, int segF, int segG, int dp);
        showInt(int number);
        // showInt2(int number);
        showFloat(float number);
        showTemperature(int number);
        changeBrightness(int value);
    private:
        lightCharacter(String string);
        lightNumber(int number);
        String numberToList(int number);
        int floatToInt(float number);
        int toFloat(float number);
        int getFloat(float number, int index, bool returnDecimalsCount);
        // getTemperature(float number, bool Float);
        int DIGIT1;
        int DIGIT2;
        int DIGIT3;
        int DIGIT4;

        int digits[4];

        int SEGA;
        int SEGB;
        int SEGC;
        int SEGD;
        int SEGE;
        int SEGF;
        int SEGG;
        int DP;

        int DISPLAY_BRIGHTNESS = 200;
};