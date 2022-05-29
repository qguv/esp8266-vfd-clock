#pragma once

extern int ntp_utc_offset_sec;
extern int ntp_update_interval_sec;

void ntp_init(void);
void ntp_fmt(char *b);
