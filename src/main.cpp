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

// portal & ota
#include <LittleFS.h>
#include <WiFiSettings.h>
#include <ArduinoOTA.h>

// ntp
#include <NTPClient.h>
#include <WiFiUdp.h>

#include <VFD.h>

#define ANIM_FRAME_MS 40
#define WIFI_TIMEOUT_SEC 15
#define ARRAY_LEN(X) (sizeof (X) / sizeof (X)[0])

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP);

bool should_blink;
int utc_offset_sec;
long update_interval_ms;

void setup_ota()
{
  ArduinoOTA.setHostname(WiFiSettings.hostname.c_str());
  ArduinoOTA.setPassword(WiFiSettings.password.c_str());
  ArduinoOTA.begin();
}

void show_time(bool blink)
{
  timeClient.update();

  String t = timeClient.getFormattedTime().c_str();
  char b[13] = "            ";
  if (t[0] != '0') b[3] = t[0];
  b[4] = t[1];
  b[6] = t[3];
  b[7] = t[4];
  if (blink) {
    b[11] = '-';
  }
  Vfd.write(b);
}

void show_characters(bool blink)
{
  static char b[13] = "            ";
  static char c = '!';
  for (int i = 0; i < 11; i++) {
    b[i] = b[i+1];
  }
  b[11] = c++;
  Vfd.write(b);
}

char * const anim_connecting[24] = {
    "->          ",
    "-->         ",
    "--->        ",
    " --->       ",
    "  --->      ",
    "   --->     ",
    "    --->    ",
    "     --->   ",
    "      --->  ",
    "       ---> ",
    "        --->",
    "         --<",
    "          <-",
    "         <--",
    "        <---",
    "       <--- ",
    "      <---  ",
    "     <---   ",
    "    <---    ",
    "   <---     ",
    "  <---      ",
    " <---       ",
    "<---        ",
    ">--         ",
};

char * const anim_config[60] = {
    "1  config   ",
    "1  config   ",
    "1  config   ",
    "1  config   ",
    ")  config   ",
    ")  config   ",
    ")  config   ",
    ")  config   ",
    " ) config   ",
    " ) config   ",
    " ) config   ",
    "  )config   ",
    "  )config   ",
    "  )config   ",
    "   )onfig   ",
    "   )onfig   ",
    "   c)nfig   ",
    "   co)fig   ",
    "   con)ig   ",
    "   conf)g   ",
    "   confi)   ",
    "   confi)   ",
    "   config)  ",
    "   config)  ",
    "   config)  ",
    "   config ) ",
    "   config ) ",
    "   config ) ",
    "   config ) ",
    "   config  )",
    "   config  )",
    "   config  1",
    "   config  1",
    "   config  (",
    "   config  (",
    "   config ( ",
    "   config ( ",
    "   config ( ",
    "   config ( ",
    "   config(  ",
    "   config(  ",
    "   config(  ",
    "   confi(   ",
    "   confi(   ",
    "   conf(g   ",
    "   con(ig   ",
    "   co(fig   ",
    "   c(nfig   ",
    "   (onfig   ",
    "   (onfig   ",
    "  (config   ",
    "  (config   ",
    "  (config   ",
    " ( config   ",
    " ( config   ",
    " ( config   ",
    "(  config   ",
    "(  config   ",
    "(  config   ",
    "(  config   ",
};

void setup()
{
  Serial.begin(115200);
  LittleFS.begin();

  pinMode(D3, OUTPUT);
  digitalWrite(D3, LOW);

  Vfd.init();
  Vfd.write("            ");

  should_blink = WiFiSettings.checkbox("should_blink", false, "Should the timer blink?");
  utc_offset_sec = WiFiSettings.integer("utc_offset_sec", 1 * 60 * 60, "UTC offset (seconds)");
  update_interval_ms = 1000L * (long) WiFiSettings.integer("update_interval_sec", 24 * 60 * 60, "NTP update interval (seconds)");

  WiFiSettings.onWaitLoop = []() {
    static unsigned long last_frame = ARRAY_LEN(anim_connecting);
    unsigned long frame = millis() / ANIM_FRAME_MS % ARRAY_LEN(anim_connecting);
    if (last_frame != frame) {
      last_frame = frame;
      Vfd.write(anim_connecting[frame]);
    }
    return 50;
  };

  WiFiSettings.onSuccess = []() {
    Vfd.write("    ota  ntp");
    delay(ANIM_FRAME_MS);
    Vfd.write(">   ota  ntp");
    delay(ANIM_FRAME_MS);
    Vfd.write("->  ota  ntp");
    delay(ANIM_FRAME_MS);
    Vfd.write("--> ota  ntp");
    setup_ota();

    Vfd.write("--->ota  ntp");
    delay(ANIM_FRAME_MS);
    Vfd.write("---->ta  ntp");
    delay(ANIM_FRAME_MS);
    Vfd.write("----->a  ntp");
    delay(ANIM_FRAME_MS);
    Vfd.write("------>  ntp");
    delay(ANIM_FRAME_MS);

    Vfd.write("-------> ntp");
    timeClient.begin();
    timeClient.setTimeOffset(utc_offset_sec);
    timeClient.setUpdateInterval(update_interval_ms);

    Vfd.write("  ------>ntp");
    delay(ANIM_FRAME_MS);
    Vfd.write("   ------>tp");
    delay(ANIM_FRAME_MS);
    Vfd.write("    ------>p");
    delay(ANIM_FRAME_MS);
    Vfd.write("     ------>");
    delay(ANIM_FRAME_MS);
    Vfd.write("      ------");
    delay(ANIM_FRAME_MS);
    Vfd.write("       -----");
    delay(ANIM_FRAME_MS);
    Vfd.write("        ----");
    delay(ANIM_FRAME_MS);
    Vfd.write("         ---");
    delay(ANIM_FRAME_MS);
    Vfd.write("          --");
    delay(ANIM_FRAME_MS);
    Vfd.write("           -");
    delay(ANIM_FRAME_MS);
    Vfd.write("            ");
  };

  WiFiSettings.onPortal = []() {
    setup_ota();
  };

  WiFiSettings.onPortalWaitLoop = []() {
    static unsigned long last_frame = ARRAY_LEN(anim_config);
    unsigned long frame = millis() / ANIM_FRAME_MS % ARRAY_LEN(anim_config);
    if (last_frame != frame) {
      last_frame = frame;
      Vfd.write(anim_config[frame]);
    }
    ArduinoOTA.handle();
  };

  WiFiSettings.connect(true, WIFI_TIMEOUT_SEC);
}

void loop()
{
  static bool blinking = false;
  show_time(blinking);
  if (should_blink) {
    blinking = !blinking;
  }
  ArduinoOTA.handle();
  delay(1000);
}
