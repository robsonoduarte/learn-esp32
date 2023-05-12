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

void setup() {
    preferences.begin("esp32", false);
    if(!preferences.isKey("ECHO")) preferences.putBool("ECHO", ECHO);
    if(!preferences.isKey("MESSAGE")) preferences.putString("MESSAGE", MESSAGE);

    Serial.begin(115200);
    SerialBT.begin(device_name);
}



void loop() {
    if(SerialBT.available()){
        String message = SerialBT.readString();
        message.trim();
        if (message == "NO_ECHO") {
            preferences.putBool("ECHO", 0);
        }
        else if (message == "ECHO") {
            preferences.putBool("ECHO", 1);
        }
        else{
            preferences.putString("MESSAGE", message);
        }
    }
    if(preferences.getBool("ECHO")){
        SerialBT.println(preferences.getString("MESSAGE"));
    }
    delay(1000);
}