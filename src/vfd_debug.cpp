#include "VFD.h"
#include "vfd_debug.h"

void show_characters(void)
{
  static char b[13] = "            ";
  static char c = '!';
  for (int i = 0; i < 11; i++) {
    b[i] = b[i+1];
  }
  b[11] = c++;
  Vfd.write(b);
}
