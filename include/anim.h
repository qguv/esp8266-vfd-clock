#pragma once

#include "VFD.h"

#define ANIM_FRAME_MS 40

void anim_overlay(char (*anim)[13], int anim_len, char *b);
void anim_string(char (*anim)[13], int anim_len, char s[13], VFD Vfd);
void anim_play(char (*anim)[13], int first, int count, VFD Vfd);
extern char anim_wave[74][13];
extern char anim_init[20][13];
