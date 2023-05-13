#include "Arduino.h"
#include "BluetoothSerial.h"
#include "Preferences.h"
#include "split.h"

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

#if !defined(CONFIG_BT_SPP_ENABLED)
#error Serial Bluetooth not available or not enabled. It is only available for the ESP32 chip.
#endif

String device_name = "ESP32 Bluetooth";

BluetoothSerial SerialBT;
Preferences preferences;

void setup() {
    preferences.begin("esp32", false);
    if(!preferences.isKey("ENABLE_ECHO")) preferences.putString("ENABLE_ECHO", ENABLE_ECHO);
    if(!preferences.isKey("MESSAGE_DELAY")) preferences.putString("MESSAGE_DELAY", MESSAGE_DELAY);
    if(!preferences.isKey("MESSAGE")) preferences.putString("MESSAGE", MESSAGE);
    SerialBT.begin(device_name);
}

void loop() {
    if(SerialBT.available()){
        String message = SerialBT.readString();
        message.trim();
        String* values = split(message, "|", 2);
        String key = values[0];
        String value = values[1];
        preferences.putString(key.c_str(), value.c_str());
    }
    if(preferences.getString("ENABLE_ECHO") == "1"){
        SerialBT.println(preferences.getString("MESSAGE"));
    }
    delay(preferences.getString("MESSAGE_DELAY").toInt());
}