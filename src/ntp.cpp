#include <NTPClient.h>
#include <WiFiUdp.h>

#include "ntp.h"

static WiFiUDP ntpUDP;
static NTPClient timeClient(ntpUDP);

int ntp_utc_offset_sec;
int ntp_update_interval_sec;

void ntp_init(void)
{
    timeClient.begin();
    timeClient.setTimeOffset(ntp_utc_offset_sec);
    timeClient.setUpdateInterval(1000L * (long) ntp_update_interval_sec);
}

void ntp_fmt(char *b)
{
  timeClient.update();
  String t = timeClient.getFormattedTime().c_str();

  b[0] = ' ';
  b[1] = ' ';
  b[2] = ' ';
  b[3] = (t[0] == '0') ? ' ' : t[0];

  b[4] = t[1];
  b[5] = ' ';
  b[6] = t[3];
  b[7] = t[4];

  b[8] = ' ';
  b[9] = ' ';
  b[10] = ' ';
  b[11] = ' ';

  b[12] = 0;
}
