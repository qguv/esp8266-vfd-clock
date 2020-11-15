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
#include <NTPClient.h>
#include <WiFiUdp.h>

#include "VFD.h"

const char* ssid = "ssid";
const char* password = "password";

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP);

void show_time()
{
	while (!timeClient.update())
		timeClient.forceUpdate();

	String t = timeClient.getFormattedTime().c_str();
        char b[13] = "            ";
        if (t[0] != '0') b[3] = t[0];
        b[4] = t[1];
        b[6] = t[3];
        b[7] = t[4];
        Vfd.write(b);
}

void setup()
{
  pinMode(D3, OUTPUT);
  digitalWrite(D3, LOW);

  Vfd.init();
  Vfd.write("            ");

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    Vfd.write("->          ");
    delay(40);
    Vfd.write("-->         ");
    delay(40);
    Vfd.write("--->        ");
    delay(40);
    Vfd.write(" --->       ");
    delay(40);
    Vfd.write("  --->      ");
    delay(40);
    Vfd.write("   --->     ");
    delay(40);
    Vfd.write("    --->    ");
    delay(40);
    Vfd.write("     --->   ");
    delay(40);
    Vfd.write("      --->  ");
    delay(40);
    Vfd.write("       ---> ");
    delay(40);
    Vfd.write("        --->");
    delay(40);
    Vfd.write("         --<");
    delay(40);
    Vfd.write("          <-");
    delay(40);
    Vfd.write("         <--");
    delay(40);
    Vfd.write("        <---");
    delay(40);
    Vfd.write("       <--- ");
    delay(40);
    Vfd.write("      <---  ");
    delay(40);
    Vfd.write("     <---   ");
    delay(40);
    Vfd.write("    <---    ");
    delay(40);
    Vfd.write("   <---     ");
    delay(40);
    Vfd.write("  <---      ");
    delay(40);
    Vfd.write(" <---       ");
    delay(40);
    Vfd.write("<---        ");
    delay(40);
    Vfd.write(">--         ");
    delay(40);
  }

  timeClient.begin();
  timeClient.setTimeOffset(3600);
}

void loop()
{
  show_time();
  delay(500);
}
