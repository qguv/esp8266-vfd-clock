// esp8266-vfd-clock
// based on VFD mumble indicator by F0x and Sebastius for Revspace.nl mumble server
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

#include <LittleFS.h>
#include <WiFiSettings.h>
#include <ArduinoOTA.h>

#include "anim.h"
#include "ntp.h"
#include "VFD.h"

#define WIFI_TIMEOUT_SEC 15
#define ARRAY_LEN(X) (sizeof (X) / sizeof (X)[0])

static void portal(void)
{
  anim_string(anim_wave, ARRAY_LEN(anim_wave), "   config   ", Vfd);
  ArduinoOTA.handle();
}

static int connecting(void)
{
  anim_string(anim_wave, ARRAY_LEN(anim_wave), " connecting ", Vfd);
  return 50;
}

static void setup_ota(void)
{
  ArduinoOTA.setHostname(WiFiSettings.hostname.c_str());
  ArduinoOTA.setPassword(WiFiSettings.password.c_str());
  ArduinoOTA.begin();
}

static void connected(void)
{
  anim_play(anim_init, 0, 4, Vfd);
  setup_ota();
  anim_play(anim_init, 4, 5, Vfd);
  ntp_init();
  anim_play(anim_init, 9, 11, Vfd);
}

void setup(void)
{
  Serial.begin(115200);
  LittleFS.begin();

  pinMode(D3, OUTPUT);
  digitalWrite(D3, LOW);

  Vfd.init();
  Vfd.write("            ");

  ntp_utc_offset_sec = WiFiSettings.integer("utc_offset_sec", 1 * 60 * 60, "UTC offset (seconds)");
  ntp_update_interval_sec = WiFiSettings.integer("update_interval_sec", 24 * 60 * 60, "NTP update interval (seconds)");

  WiFiSettings.onWaitLoop = connecting;
  WiFiSettings.onSuccess = connected;
  WiFiSettings.onPortal = setup_ota;
  WiFiSettings.onPortalWaitLoop = portal;
  WiFiSettings.connect(true, WIFI_TIMEOUT_SEC);
}

void loop(void)
{
  char b[13];
  ntp_fmt(b);
  Vfd.write(b);
  ArduinoOTA.handle();
  delay(100);
}
