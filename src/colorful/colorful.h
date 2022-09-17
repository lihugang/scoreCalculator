#pragma once

#ifndef __INC_COLORFUL_
#define __INC_COLORFUL_
#ifndef NOCOLORFUL
#define _COLORFUL(displayMethod, frontColor, backgroundColor, str) \
  "\033[" displayMethod ";" frontColor ";" backgroundColor "m" str "\033[0m"
#define _COLORFUL_WITHOUT_BKG(displayMethod, frontColor, str) \
  "\033[" displayMethod ";" frontColor "m" str "\033[0m"
#else
#define _COLORFUL(_a, _b, _c, str) str
#define _COLORFUL_WITHOUT_BKG(_a, _b, str) str
#endif

#define _DISPLAY_DEFAULT "0"
#define _DISPLAY_HIGHLIGHT "1"
#define _DISPLAY_NOT_BOLD "22"
#define _DISPLAY_UNDERLINE "4"
#define _DISPLAY_NOT_UNDERLINE "24"
#define _DISPLAY_FLASH "5"
#define _DISPLAY_NOT_FLASH "25"
#define _DISPLAY_COMP "7"
#define _DISPLAY_NOT_COMP "27"

#define _FCOLOR_BLACK "30"
#define _FCOLOR_RED "31"
#define _FCOLOR_GREEN "32"
#define _FCOLOR_YELLOW "33"
#define _FCOLOR_BLUE "34"
#define _FCOLOR_MAGENTA "35"
#define _FCOLOR_CYAN "36"
#define _FCOLOR_WHITE "37"

#define _BCOLOR_BLACK "40"
#define _BCOLOR_RED "41"
#define _BCOLOR_GREEN "42"
#define _BCOLOR_YELLOW "43"
#define _BCOLOR_BLUE "44"
#define _BCOLOR_MAGENTA "45"
#define _BCOLOR_CYAN "46"
#define _BCOLOR_WHITE "47"

#define _PRINT_BLACK(x) \
  _COLORFUL_WITHOUT_BKG(_DISPLAY_DEFAULT, _FCOLOR_BLACK, x)
#define _PRINT_RED(x) _COLORFUL_WITHOUT_BKG(_DISPLAY_DEFAULT, _FCOLOR_RED, x)
#define _PRINT_GREEN(x) \
  _COLORFUL_WITHOUT_BKG(_DISPLAY_DEFAULT, _FCOLOR_GREEN, x)
#define _PRINT_YELLOW(x) \
  _COLORFUL_WITHOUT_BKG(_DISPLAY_DEFAULT, _FCOLOR_GREEN, x)
#define _PRINT_BLUE(x) _COLORFUL_WITHOUT_BKG(_DISPLAY_DEFAULT, _FCOLOR_BLUE, x)
#define _PRINT_MAGENTA(x) \
  _COLORFUL_WITHOUT_BKG(_DISPLAY_DEFAULT, _FCOLOR_MAGENTA, x)
#define _PRINT_CYAN(x) _COLORFUL_WITHOUT_BKG(_DISPLAY_DEFAULT, _FCOLOR_CYAN, x)
#define _PRINT_WHITE(x) \
  _COLORFUL_WITHOUT_BKG(_DISPLAY_DEFAULT, _FCOLOR_WHITE, x)
#endif