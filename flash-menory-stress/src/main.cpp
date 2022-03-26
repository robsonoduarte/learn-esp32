#include "Arduino.h"
#include "Preferences.h"

#ifndef LED_BUILTIN
#define LED_BUILTIN 13
#endif


Preferences preferences;
long maxCountSave = 5001000;
long counter;


void setup() {
    Serial.begin(9600);
    pinMode(LED_BUILTIN, OUTPUT);
    preferences.begin("flash-memory", false);
    counter = preferences.getLong("counter");
    digitalWrite(LED_BUILTIN, HIGH);
}

void loop() {
    if (counter <= maxCountSave) {
        preferences.putLong("counter", counter++);
    } else {
        long c = preferences.getLong("counter");
        Serial.println(c);
        digitalWrite(LED_BUILTIN, HIGH);
        delay(1000);
        digitalWrite(LED_BUILTIN, LOW);
        delay(1000);
    }
}
