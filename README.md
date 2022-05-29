# esp8266-vfd-clock

A clock on a VFD display driven by an esp8266

## building

- install platform.io command-line tools
- connect an esp8266
- make it programmable
  - cut power
  - hold reset
  - restore power while still holding reset
  - wait a couple seconds
  - release reset
- `pio run -t upload`
