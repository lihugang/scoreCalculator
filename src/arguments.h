#pragma once
#ifndef _INC_ARG__
#define _INC_ARG__
#include "debug/macro.h"
typedef struct _arguments  ARGUMENTS;

#define _MAX_FILEPATH_LEN 4200 //for windows 260, linux default 4096

void parse_cli_arguments(_IN int cli_argc, _IN char **cli_argv, _OUT ARGUMENTS * args);

#include "arguments.c"
#endif