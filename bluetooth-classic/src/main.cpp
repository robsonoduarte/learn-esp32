#include "Arduino.h"
#include "BluetoothSerial.h"
#include "Preferences.h"


String device_name = "ESP32 Bluetooth";

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

#if !defined(CONFIG_BT_SPP_ENABLED)
#error Serial Bluetooth not available or not enabled. It is only available for the ESP32 chip.
#endif

BluetoothSerial SerialBT;
Preferences preferences;

String message = MESSAGE;

void setup() {
    preferences.begin("esp32", false);
    preferences.putBool("ECHO", ECHO);

    Serial.begin(115200);
    SerialBT.begin(device_name);
}



void loop() {
    while (SerialBT.available()){
        message += String(SerialBT.read());
    }
    if(preferences.getBool("ECHO")){
        SerialBT.println(message);
    }
    delay(1000);
}