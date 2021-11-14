/*#################################################################################
 * This library was produced by Halina
 * 
 *  github: https://github.com/halina20011/Arduino-SH5461AS-library
###################################################################################*/
#include "Arduino.h"
#include "SH5461AS.h"

SH5461AS::SH5461AS(int digit1, int digit2, int digit3, int digit4, int segA, int segB, int segC, int segD, int segE, int segF, int segG, int dp){
    DIGIT1 = digit1;
    DIGIT2 = digit2;
    DIGIT3 = digit3;
    DIGIT4 = digit4;

    digits[0] = digit1;
    digits[1] = digit2;
    digits[2] = digit3;
    digits[3] = digit4;

    SEGA = segA;
    SEGB = segB;
    SEGC = segC;
    SEGD = segD;
    SEGE = segE;
    SEGF = segF;
    SEGG = segG;

    DP = dp;

    pinMode(SEGA, OUTPUT);
    pinMode(SEGB, OUTPUT);
    pinMode(SEGC, OUTPUT);
    pinMode(SEGD, OUTPUT);
    pinMode(SEGE, OUTPUT);
    pinMode(SEGF, OUTPUT);
    pinMode(SEGG, OUTPUT);

    pinMode(DIGIT1, OUTPUT);
    pinMode(DIGIT2, OUTPUT);
    pinMode(DIGIT3, OUTPUT);
    pinMode(DIGIT4, OUTPUT);
    pinMode(DP, OUTPUT);
    return;
}

SH5461AS::changeBrightness(int value){
    DISPLAY_BRIGHTNESS = value;
    return;
}

SH5461AS::showInt(int number){
    // unsigned long t = millis();
    String arrayN[6];
    String arrayS;

    arrayS = numberToList(number);

    for(int i = 0; i < arrayS.length(); i++){
        String b = arrayS.substring(i, i + 1);
        arrayN[i] = b;
    }

    for(int x = 0; x < 50; x++){
        for(int i = 1; i < 5; i++){
            if(i == 1 && arrayN[3] != "-"){
                digitalWrite(DIGIT4, LOW); //
                lightNumber(arrayN[3].toInt());
                delayMicroseconds(DISPLAY_BRIGHTNESS);
            }
            else if(i == 2 && arrayN[2] != "-") {
                // Serial.println(arrayN[2].toInt());
                digitalWrite(DIGIT3, LOW); //
                lightNumber(arrayN[2].toInt());
                delayMicroseconds(DISPLAY_BRIGHTNESS);
            }
            else if(i == 3 && arrayN[1] != "-") {
                digitalWrite(DIGIT2, LOW); //
                lightNumber(arrayN[1].toInt());
                delayMicroseconds(DISPLAY_BRIGHTNESS);
            }
            else if(i == 4 && arrayN[0] != "-") {
                // Serial.println(arrayN[0].toInt());
                digitalWrite(DIGIT1, LOW); //
                lightNumber(arrayN[0].toInt());
                delayMicroseconds(DISPLAY_BRIGHTNESS);
            }
            lightNumber(10);

            digitalWrite(DIGIT4, HIGH);
            digitalWrite(DIGIT3, HIGH);
            digitalWrite(DIGIT2, HIGH);
            digitalWrite(DIGIT1, HIGH);
        }
    }
    // Serial.print("Time F2 :");
    // unsigned long t2= millis() - t;
    // Serial.println(t2);
    return 0;
}   

// SH5461AS::showInt(int number){
//     unsigned long t = millis();
//     bool duiz = false;
//     bool hon = false;
//     for (int k = 0; k < 50; k++) {
//         int newNumber = number;
//         for (int digit = 1 ; digit < 5 ; digit++) {
//             switch (digit) {
//                 case 1:
//                 if (newNumber > 999) {
//                     digitalWrite(DIGIT1, LOW);
//                     lightNumber(newNumber / 1000);            // for example 2511 / 1000 = 2
//                     newNumber %= 1000;                        // new value of newNumber = 511         newNumber = newNumber %1000
// 
//                     delayMicroseconds(DISPLAY_BRIGHTNESS);
//                     if (newNumber < 100) {
//                         duiz = true;
//                         if (newNumber < 10) {
//                             hon = true;
//                         }
//                     } 
//                     else {
//                         duiz = false;
//                     }
//                 }
// 
//                 break;
//                 case 2:
//                 if (duiz == true) {
//                     digitalWrite(DIGIT2, LOW);
//                     lightNumber(0);
//                     delayMicroseconds(DISPLAY_BRIGHTNESS);
// 
//                 } if (hon == true) {
//                     break;
//                 }
// 
//                 if (newNumber > 99 && newNumber < 1000) {
//                     digitalWrite(DIGIT2, LOW);
//                     lightNumber(newNumber / 100);
//                     newNumber %= 100;
//                     delayMicroseconds(DISPLAY_BRIGHTNESS);
//                     if (newNumber < 10) {
//                     hon = true;
// 
//                     } else hon = false;
//                 }
// 
//                 break;
//                 case 3:
//                 if (hon == true) {
//                     digitalWrite(DIGIT3, LOW);
//                     lightNumber(0);
//                     delayMicroseconds(DISPLAY_BRIGHTNESS);
//                     break;
//                 }
// 
//                 if (newNumber > 9 && newNumber < 100) {
//                     digitalWrite(DIGIT3, LOW);
//                     lightNumber(newNumber / 10);
//                     newNumber %= 10;
//                     delayMicroseconds(DISPLAY_BRIGHTNESS);
//                 }
// 
//                 break;
//                 case 4:
//                 if (newNumber < 10) {
//                     digitalWrite(DIGIT4, LOW);
//                     lightNumber(newNumber);
//                     delayMicroseconds(DISPLAY_BRIGHTNESS);
//                     break;
//                 }
//             }
//             lightNumber(10);    
// 
//             digitalWrite(DIGIT1, HIGH);
//             digitalWrite(DIGIT2, HIGH);
//             digitalWrite(DIGIT3, HIGH);
//             digitalWrite(DIGIT4, HIGH);
//         }
//     }
//     Serial.print("Time F1 :");
//     unsigned long t2= millis() - t;
//     Serial.println(t2);
// }

SH5461AS::showFloat(float number){
    int lengthInt = floatToInt(number);
    int decimal1 = getFloat(number, 1, false);
    int decimal2 = getFloat(number, 2, false);
    int decimals = getFloat(number, 0, true);

    // Serial.print("LengthInt: ");
    // Serial.print(lengthInt);
    // Serial.print(decimal1);
    // Serial.print(" decimal1: ");
    // Serial.print("decimal2: ");
    // Serial.println(decimal2);
    // Serial.println(" ");

    String decimalHole = "";
    // Serial.print("Decimals: ");
    // Serial.println(decimals);

    if(decimals == 1){
        decimalHole = "-";
    }

    String returnString = "";

    if(lengthInt < 10){
        returnString = decimalHole + "-" + String(lengthInt) + "."+ String(decimal1) + String(decimal2);
    }
    else if(lengthInt < 100){
        returnString = decimalHole + String(lengthInt) + "." + String(decimal1) + String(decimal2);
    }
    else if(lengthInt < 1000){
        returnString = String(lengthInt) + "." + String(decimal1);
    }
    else if(lengthInt < 10000){
        returnString = decimalHole + String(lengthInt);
    }

    String arrayN[6];

    for(int i = 0; i < returnString.length(); i++){
        String b = returnString.substring(i, i + 1);
        arrayN[i] = b;
    }

    // for(int i = 0; i < 6; i++){
    //     Serial.print(arrayN[i]);
    // }
    // Serial.println("");

    for(int x = 0; x < 50; x++){
        int minus = 0;
        for(int i = 0; i < 5; i++){
            int copy = i - minus;
            if(arrayN[i] == "-"){
                minus += 0;
            }
            else if(arrayN[i] == "."){
                digitalWrite(digits[copy - 1], LOW);
                lightCharacter(".");
                minus +=1;
            }
            else{
                digitalWrite(digits[copy], LOW);
                lightNumber(arrayN[i].toInt());
                delayMicroseconds(DISPLAY_BRIGHTNESS);
            }
            lightNumber(10);

            digitalWrite(DIGIT4, HIGH);
            digitalWrite(DIGIT3, HIGH);
            digitalWrite(DIGIT2, HIGH);
            digitalWrite(DIGIT1, HIGH);
        }
    }
    return 0;
}

SH5461AS::showTemperature(int number){
    bool positive = 1;

    if(number < 0){
        positive = 0;
        number = number * -1;
    }

    // int N = floatToInt(number);
    String t = "oC";

    String returnString = "";

    if(number < 10){
        if(positive == 1){
            returnString = "-" + String(number) + t;
        }
        else if(positive == 0 && number > -10){
            returnString = "x" + String(number) + t;
        }
    }
    else if(number < 100 && positive == 0){
        returnString = "x" + String(number) + "C";
    }
    else if(number < 100){
        returnString = String(number) + t;
    }
    else if(number < 1000){
        if(positive == 1){
            returnString = String(number) + "C";
        }
    }
    else if(number < 10000){
        if(positive == 1){
            returnString = String(number);
        }
    }

    // Serial.println(returnString);
    String arrayN[6];

    for(int i = 0; i < returnString.length(); i++){
        String b = returnString.substring(i, i + 1);
        arrayN[i] = b;
    }

    for(int i = 0; i < 6; i++){
        Serial.print(arrayN[i]);
    }
    Serial.println("");

    for(int x = 0; x < 50; x++){
        for(int i = 0; i < 5; i++){
            if(arrayN[i] == "-"){
            }
            else if(arrayN[i] == "o"){
                digitalWrite(digits[i], LOW);
                lightCharacter("°");
                delayMicroseconds(DISPLAY_BRIGHTNESS);
            }
            else if(arrayN[i] == "x"){
                digitalWrite(digits[i], LOW);
                lightCharacter("-");
                delayMicroseconds(DISPLAY_BRIGHTNESS);
            }
            else if(arrayN[i] == "C"){
                digitalWrite(digits[i], LOW);
                lightCharacter("C");
                delayMicroseconds(DISPLAY_BRIGHTNESS);
            }
            else{
                digitalWrite(digits[i], LOW);
                lightNumber(arrayN[i].toInt());
                delayMicroseconds(DISPLAY_BRIGHTNESS);
            }
            lightNumber(10);

            digitalWrite(DIGIT4, HIGH);
            digitalWrite(DIGIT3, HIGH);
            digitalWrite(DIGIT2, HIGH);
            digitalWrite(DIGIT1, HIGH);
        }
    }
    return 0;
}

// SH5461AS::getTemperature(float number, bool isFloat){
//     String returnString;
//     int lengthInt = floatToInt(number);
//     int decimal1 = getFloat(number, 0, false);
//     int decimal2 = getFloat(number, 0, false);
//     bool decimals = getFloat(number, 0, true);
//     Serial.print(lengthInt);
//     Serial.print(decimal1);
//     Serial.print(decimal2);
//     Serial.print(decimals);
//     return;
// }

int SH5461AS::floatToInt(float number){
    float value = number;
    int intPart = (int)(value);
    return intPart;
}

int SH5461AS::toFloat(float number){
    float nn = number;
    String dd = String(nn, 2);
    return dd.toInt();
}

int SH5461AS::getFloat(float number, int index, bool returnDecimalsCount){
    // Serial.print("Number is: ");

    // imagine that number is 19.21.
    float numberInt = int(number); //Value will be 19.
    float numberFloat = number - numberInt; //Float will be 19.21 - 19 = 0.21.

    //To check if number have only one decimal (0.2) (0.22) is two decimal.
    float firstDecimal = numberFloat * 10; //We will _float (the result from above) multiply by 10 to get 0.21 * 10 = 2.10.
    float float1 = toFloat(firstDecimal); //Value2 will be 2 (because is it int). int(2.10) = 2

    float secondDecimal = (firstDecimal - float1) * 10; //We will (2.10 - 2) = 0.10 multiply by 10 to get 0.10 * 10 = 1.00.
    float float2 = toFloat(secondDecimal); //Value2 will be 2 (because is it int). int(1.00) = 1

    // int decimalOne = _float * 10; // 0.21 * 10 = 2
    // int decimalTwo = toFloat(_float2 * 10);
    int decimalOne = int(float1);
    int decimalTwo = int(float2);
    // int decimalTwo = _float2 * 10;

    // float nn = _float2 * 10;
    // String dd = String(nn, 2);
    // int decimalTwo = dd.toInt();
    
    // Serial.print("Number2: ");
    // Serial.println(number2);
    // Serial.print("Value: ");
    // Serial.println(value);
    // Serial.println("");
    // Serial.print("Value2: ");
    // Serial.println(value2);
    // Serial.print("DecimalOne: ");
    // Serial.println(decimalOne);
    // Serial.print("DecimalTwo: ");
    // Serial.println(decimalTwo);

    // Serial.println("");
    // Serial.print("Decimal One: ");
    // Serial.println(decimalOne);
    // Serial.print("Decimal Two: ");
    // Serial.println(decimalTwo);

    if(index == 1){
        return decimalOne;
    }
    else if(index == 2){
        return decimalTwo;
    }
    // return|  decimalOne | decimalTwo |
    //   0   |      0      |      0     |
    //   1   |      1<     |      0     |
    //   2   |      0      |      1<    |
    //   3   |      1<     |      1<    |

    int decimals = 0;

    if(decimalOne == 0 && decimalTwo == 0){
        decimals = 0;
    }
    else if(decimalOne >= 1 && decimalTwo == 0){
        decimals = 1;
    }
    else if(decimalOne == 0 && decimalTwo >= 1){
        decimals = 2;
    }
    else if(decimalOne >= 1 && decimalTwo >= 1){
        decimals = 3;
    }

    // Serial.println("Ten is: ");
    // Serial.println(twoDecimal);
    // Serial.println("Hole is: ");
    // Serial.println(value2);
    // Serial.println("Float is: ");
    // Serial.println(_floa2);

    if(returnDecimalsCount){
        return decimals;
    }
    return 0;
}

String SH5461AS::numberToList(int number){
    String arrayN[4];
    String arrayS;
    String a = String(number);
    int _length = a.length();
    int index = 0;
    if(_length != 4){
        if(_length == 3){
        arrayN[0] = "-";
        index += 1;
        }
        else if(_length == 2){
        arrayN[0] = "-";
        arrayN[1] = "-";
        index += 2;
        }
        else if(_length == 1){
        arrayN[0] = "-";
        arrayN[1] = "-";
        arrayN[2] = "-";
        index += 3;
        }
        else if(_length <= 0){
            return arrayS;
        }
    }
    for(int i = 0; i < a.length(); i++){
        String b = a.substring(i, i + 1);
        arrayN[i + index] = b;
    }
    for(int i = 0 ; i < 4; i++){
        if(arrayN[i] != ""){
        arrayS += arrayN[i]; 
        }
    }
    return arrayS;
}
//     a
//    ----
// f |    | b
//    ----
// e | g  | c
//    ----
//     d
SH5461AS::lightCharacter(String character){
    if(character == "."){
        digitalWrite(DP, HIGH);
    }
    else if(character == "C"){
        digitalWrite(SEGA, HIGH);
        digitalWrite(SEGB, LOW);
        digitalWrite(SEGC, LOW);
        digitalWrite(SEGD, HIGH);
        digitalWrite(SEGE, HIGH);
        digitalWrite(SEGF, HIGH);
        digitalWrite(SEGG, LOW);
    }
    else if(character == "-"){
        digitalWrite(SEGA, LOW);
        digitalWrite(SEGB, LOW);
        digitalWrite(SEGC, LOW);
        digitalWrite(SEGD, LOW);
        digitalWrite(SEGE, LOW);
        digitalWrite(SEGF, LOW);
        digitalWrite(SEGG, HIGH);
    }
    else if(character == "°"){
        digitalWrite(SEGA, HIGH);
        digitalWrite(SEGB, HIGH);
        digitalWrite(SEGC, LOW);
        digitalWrite(SEGD, LOW);
        digitalWrite(SEGE, LOW);
        digitalWrite(SEGF, HIGH);
        digitalWrite(SEGG, HIGH);
    }
    else{
        Serial.println("Error");
    }
    return;
}

SH5461AS::lightNumber(int number){
    if(number == 0){
        digitalWrite(SEGA, HIGH);
        digitalWrite(SEGB, HIGH);
        digitalWrite(SEGC, HIGH);
        digitalWrite(SEGD, HIGH);
        digitalWrite(SEGE, HIGH);
        digitalWrite(SEGF, HIGH);
        digitalWrite(SEGG, LOW);
        return 0;
    }
    else if(number == 1){
        digitalWrite(SEGA, LOW);
        digitalWrite(SEGB, HIGH);
        digitalWrite(SEGC, HIGH);
        digitalWrite(SEGD, LOW);
        digitalWrite(SEGE, LOW);
        digitalWrite(SEGF, LOW);
        digitalWrite(SEGG, LOW);
        return 0;
    }
    else if(number == 2){
        digitalWrite(SEGA, HIGH);
        digitalWrite(SEGB, HIGH);
        digitalWrite(SEGC, LOW);
        digitalWrite(SEGD, HIGH);
        digitalWrite(SEGE, HIGH);
        digitalWrite(SEGF, LOW);
        digitalWrite(SEGG, HIGH);
        return 0;
    }
    else if(number == 3){
        digitalWrite(SEGA, HIGH);
        digitalWrite(SEGB, HIGH);
        digitalWrite(SEGC, HIGH);
        digitalWrite(SEGD, HIGH);
        digitalWrite(SEGE, LOW);
        digitalWrite(SEGF, LOW);
        digitalWrite(SEGG, HIGH);
        return 0;
    }
    else if(number == 4){
        digitalWrite(SEGA, LOW);
        digitalWrite(SEGB, HIGH);
        digitalWrite(SEGC, HIGH);
        digitalWrite(SEGD, LOW);
        digitalWrite(SEGE, LOW);
        digitalWrite(SEGF, HIGH);
        digitalWrite(SEGG, HIGH);
        return 0;
    }
    else if(number == 5){
        digitalWrite(SEGA, HIGH);
        digitalWrite(SEGB, LOW);
        digitalWrite(SEGC, HIGH);
        digitalWrite(SEGD, HIGH);
        digitalWrite(SEGE, LOW);
        digitalWrite(SEGF, HIGH);
        digitalWrite(SEGG, HIGH);
        return 0;
    }
    else if(number == 6){
        digitalWrite(SEGA, HIGH);
        digitalWrite(SEGB, LOW);
        digitalWrite(SEGC, HIGH);
        digitalWrite(SEGD, HIGH);
        digitalWrite(SEGE, HIGH);
        digitalWrite(SEGF, HIGH);
        digitalWrite(SEGG, HIGH);
        return 0;
    }
    else if(number == 7){
        digitalWrite(SEGA, HIGH);
        digitalWrite(SEGB, HIGH);
        digitalWrite(SEGC, HIGH);
        digitalWrite(SEGD, LOW);
        digitalWrite(SEGE, LOW);
        digitalWrite(SEGF, LOW);
        digitalWrite(SEGG, LOW);
        return 0;
    }
    else if(number == 8){
        digitalWrite(SEGA, HIGH);
        digitalWrite(SEGB, HIGH);
        digitalWrite(SEGC, HIGH);
        digitalWrite(SEGD, HIGH);
        digitalWrite(SEGE, HIGH);
        digitalWrite(SEGF, HIGH);
        digitalWrite(SEGG, HIGH);
        return 0;
    }
    else if(number == 9){
        digitalWrite(SEGA, HIGH);
        digitalWrite(SEGB, HIGH);
        digitalWrite(SEGC, HIGH);
        digitalWrite(SEGD, HIGH);
        digitalWrite(SEGE, LOW);
        digitalWrite(SEGF, HIGH);
        digitalWrite(SEGG, HIGH);
        return 0;
    }
    else if(number == 10){
        digitalWrite(SEGA, LOW);
        digitalWrite(SEGB, LOW);
        digitalWrite(SEGC, LOW);
        digitalWrite(SEGD, LOW);
        digitalWrite(SEGE, LOW);
        digitalWrite(SEGF, LOW);
        digitalWrite(SEGG, LOW);
        digitalWrite(DP, LOW);
        return 0;
    }
}