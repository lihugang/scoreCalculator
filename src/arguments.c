#pragma once
#include "arguments.h"

#include <stdlib.h>
#include <string.h>

#include "debug/macro.h"

typedef struct _arguments {
  char filepath[_MAX_FILEPATH_LEN];
  int options_len;
  char **options;
  int not_used_counters;  // for not show un-used parameter
} ARGUMENTS;

void parse_cli_arguments(_IN int cli_argc, _IN char **cli_argv,
                         _OUT ARGUMENTS *args) {
  // format: scl xxx.xxx -options
  assert_not_null(args);

  args->filepath[0] = '\0';
  args->options = NULL;
  args->options_len = 0;
  args->not_used_counters = 0;
  // clear args

  if (cli_argc > 1) {
    assert_not_null(cli_argv[1]);
    strncpy(args->filepath, cli_argv[1], _MAX_FILEPATH_LEN - 1);
  };

  debug_int(cli_argc);

  for (int i = 2; i < cli_argc; ++i) {
    debug_str(cli_argv[i]);
    // foreach options
    assert_not_null(cli_argv[i]);
    if (cli_argv[i][0] == '\0') continue;                // the end of string
    if (cli_argv[i][0] == '-' && cli_argv[i][1] == '-')  // options
      ++(args->options_len);
  };

  alloc_memory_with_check(args->options, args->options_len * sizeof(char *));
  // allocating memory for the options array
  for (int i = 2; i < cli_argc; ++i) {
    // copy options
    if (cli_argv[i][0] == '\0') continue;                  // the end of string
    if (cli_argv[i][0] == '-' && cli_argv[i][1] == '-') {  // options
      static int argv_len = 0;
      argv_len = strlen(cli_argv[i]) - 2;  // get the length of the argument

      alloc_memory_with_check(args->options[i - 2],
                              sizeof(char) * (argv_len + 1));

      strncpy(args->options[i - 2], cli_argv[i] + 2 /* remove the '--' flag */,
              argv_len);
      debug_str(args->options[i - 2]);
    };
  };
};