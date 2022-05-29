# esp8266-vfd-clock

A clock on a VFD display driven by an esp8266.

## initial setup

1. install the platformio core CLI tools
2. plug an esp8266 into your computer
3. make it programmable:
  - cut power
  - hold reset
  - restore power while still holding reset
  - wait a couple seconds
  - release reset
4. run `pio run -t upload -e serial`
5. after 15 seconds (`WIFI_TIMEOUT_SEC`), a new wifi network will appear
6. connect to the new wifi network, which will be esp8266-xxxxxx. Take note of this name!
7. visit http://192.168.4.1
8. enter wifi credentials and UTC offset, then click 'save'
9. connect a Samsung HCS-12SS59T vacuum fluorescent display according to the chart in the **display wiring** section below
10. click 'Restart device'

## display wiring

ESP | VFD
--- | ---
VU  |  5v
GND |  GND
D0  |  RST
D1  |  CS
D2  |  VFD\_ON
D5  |  CLK
D7  |  DIN

## over-the-air updates

To configure your machine to flash the device over local wifi:

1. ensure port 8266 on your dev machine is open for LAN traffic
2. open platformio.ini
3. set `upload_port` to the name of the device's wifi network, with '.local' appended
4. set the `--auth` flag in `upload_flags` to the password for the device's wifi network

Now you can run `platformio run -t upload -e ota` to update the device as long as:

- the device is reachable from your computer's network
- the device is regularly calling `ArduinoOTA.handle();`
- mDNS is configured properly on your dev machine
