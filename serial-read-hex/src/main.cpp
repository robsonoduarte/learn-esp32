#include "Arduino.h"

void setup() {
    Serial.begin(9600);
}

void loop() {
    while (!Serial.available());
    while (Serial.available() > 0) {
        int number = Serial.read();
        Serial.print("Decimal read => ");
        Serial.print(number);
        Serial.print(" to Hex => ");
        Serial.println(number, HEX);
    }
}