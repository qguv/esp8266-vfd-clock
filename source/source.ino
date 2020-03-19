// VFD Mumble indicator
// F0x and Sebastius for Revspace.nl mumble server
// Yolo just take what you need for your projects and share alike!

// Connect hardware as follows
// ESP  -  VFD
// VU   -  5v
// GND  -  GND
// D0   -  RST
// D1   -  CS
// D2   -  VFD_ON
// D5   -  CLK
// D7   -  DIN

#include <Arduino.h>
#if defined(ARDUINO_ARCH_ESP8266)
#include <ESP8266WiFi.h>
#else
#include <WiFi.h>
#endif
#include <WiFiUdp.h>

#include "VFD.h"


const char* ssid = "SSID";
const char* password = "PASS";

const char* address = "revspace.nl";
const int port = 64738;

WiFiUDP udp;

struct __attribute__ ((packed)) mumbleRequest {
  unsigned int command;
  unsigned long long ident;
};

byte reqBuffer[12];
char respBuffer[24];



void setup()
{
  //pinMode(Pin_RED_LED13, OUTPUT);
  //digitalWrite(Pin_RED_LED13, HIGH);
  pinMode(D3, OUTPUT);
  digitalWrite(D3, LOW);
  Serial.begin(115200);
  Vfd.init();
  Vfd.write("Connecting Wifi");
  Serial.println("VFD Demo");
  //WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println();
  while (WiFi.status() != WL_CONNECTED) {
    delay(100);
    Serial.print(".");
  }
  Serial.println("Done connecting");
  udp.begin(port);

}

int mompelaars = 99;
int mompelaars_oud = 0;

void loop()
{
  mompelaars_oud = mompelaars;
  mompelaars = mumblers();
  if (mompelaars_oud != mompelaars) {
    fadeout();
    char data[12];

    if ((mompelaars == 0) || (mompelaars > 1)) {
      sprintf(data, "%u mumblers  ", mompelaars);

    } else {
      sprintf(data, "%u mumbler   ", mompelaars);
    }
    Serial.println(data);
    Vfd.write("            "); // clear screen ;)
    Vfd.write(data);

    Serial.println();
    fadein();

  } else {
    //Serial.print("");
    delay(100);
  }
}


int mumblers() {
  mumbleRequest request = {
    .command = 0,
    .ident = millis()
  };

  memcpy(reqBuffer, &request, sizeof(request));
  udp.beginPacket(address, port);
  udp.write(reqBuffer, 12);
  udp.endPacket();

  udp.parsePacket();
  udp.read(respBuffer, 24);
  // 4 bytes version
  // 8 bytes ident
  // 4 bytes connected
  // 4 bytes maximum connections
  // 4 bytes bandwidth
  int connectedpeople = respBuffer[15];
  return (connectedpeople);
}

void fadein()
{
  for (int i = 1; i <= 15; i++) {
    Vfd.setDuty(i);
    delay(80);
  }
}

void fadeout()
{
  for (int i = 1; i <= 15; i++) {
    Vfd.setDuty(16 - i);
    delay(80);
  }
}
