### Read Hex in Serial with ESP32 And Arduino Framework

simple project how we can read hex on Serial.


to upload:
```shell
pio run -e nodemcu-32s -t upload
```

to monitor serial:
```shell
pio device monitor
```

to send hex:
```shell
echo -en '\xAA\x05\x26' > /dev/ttyUSB0
```

to see the port:
```shell
pio device list
```