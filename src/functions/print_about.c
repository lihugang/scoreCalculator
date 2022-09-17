#include <stdio.h>

#include "../colorful/colorful.h"
#include "../version"
void print_about(void) {
  printf("Score Calculator\nVersion: %d.%d.%d\n", __MAJOR_VERSION__,
         __MINOR_VERSION__, __PATCH_VERSION__);
  printf("Author: https://github.com/lihugang\n");

#ifndef NOCOLORFUL
  printf("Colorful: true\n");
#else
  printf("Colorful: false\n");
#endif
#ifndef NOCOLLECTFILE
  printf("Collecting input file: true\n");
#else
  printf("Collecting input file: false\n");
#endif
#ifndef NODOWNLOADSEATTABLE
  printf("Download seat table: true\n");
#else
  printf("Download seat table: false\n");
#endif

#ifdef DEBUG
  printf("Compile mode: DEBUG\n");
#else
  printf("Compile mode: RELEASE\n");
#endif
  printf("Compile time: %s %s\n", __DATE__, __TIME__);
};