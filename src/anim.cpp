#include <Arduino.h>
#include <VFD.h>

#include "anim.h"

void anim_overlay(char (*anim)[13], int anim_len, char *b)
{
  static int last_frame = anim_len;
  int frame = millis() / ANIM_FRAME_MS % anim_len;

  if (last_frame == frame) {
    return;
  }
  last_frame = frame;

  for (int i = 0; i < 12; i++) {
    char c = anim[frame][i];
    if (c != ' ') {
      b[i] = c;
    }
  }
  b[12] = 0;
}

void anim_string(char (*anim)[13], int anim_len, char s[13], VFD Vfd)
{
  char b[13];
  for (int i = 0; i < 12; i++) {
    b[i] = s[i];
  }
  b[12] = 0;
  anim_overlay(anim, anim_len, b);
  Vfd.write(b);
}

void anim_play(char (*anim)[13], int first, int count, VFD Vfd)
{
    for (int i = first; i < first + count; i++) {
      if (i != first) {
        delay(ANIM_FRAME_MS);
      }
      Vfd.write(anim_init[i]);
    };
}

char anim_wave[74][13] = {
    "           1",
    "           1",
    "           1",
    "           1",
    "           (",
    "           (",
    "           (",
    "           (",
    "           (",
    "          ( ",
    "          ( ",
    "          ( ",
    "          ( ",
    "         (  ",
    "         (  ",
    "         (  ",
    "         (  ",
    "        (   ",
    "        (   ",
    "        (   ",
    "       (    ",
    "       (    ",
    "      (     ",
    "     (      ",
    "    (       ",
    "   (        ",
    "   (        ",
    "  (         ",
    "  (         ",
    "  (         ",
    " (          ",
    " (          ",
    " (          ",
    "(           ",
    "(           ",
    "(           ",
    "(           ",
    "1           ",
    "1           ",
    "1           ",
    "1           ",
    ")           ",
    ")           ",
    ")           ",
    ")           ",
    ")           ",
    " )          ",
    " )          ",
    " )          ",
    " )          ",
    "  )         ",
    "  )         ",
    "  )         ",
    "  )         ",
    "   )        ",
    "   )        ",
    "   )        ",
    "    )       ",
    "    )       ",
    "     )      ",
    "      )     ",
    "       )    ",
    "        )   ",
    "        )   ",
    "         )  ",
    "         )  ",
    "         )  ",
    "          ) ",
    "          ) ",
    "          ) ",
    "           )",
    "           )",
    "           )",
    "           )",
};

char anim_init[20][13] = {

  // #0 (4x)
  "    ota  ntp",
  "]   ota  ntp",
  ")]  ota  ntp",
  "))] ota  ntp",

  // #4 (5x)
  ")))]ota  ntp",
  "))))]ta  ntp",
  ")))))]a  ntp",
  "))))))]  ntp",
  ")))))))] ntp",

  // #9 (11x)
  "  ))))))]ntp",
  "   ))))))]tp",
  "    ))))))]p",
  "     ))))))]",
  "      ))))))",
  "       )))))",
  "        ))))",
  "         )))",
  "          ))",
  "           )",
  "            ",
};
