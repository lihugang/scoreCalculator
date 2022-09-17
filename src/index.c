#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "3rd-party/curl/curl.h"
#include "colorful/colorful.h"
#include "debug/macro.h"
#include "functions/generate_task.h"
#include "functions/print_about.h"
#include "functions/run_tasks.h"

TASK_LIST *tasks;

void at_exit_cleanup(void) {
  curl_global_cleanup();
  free(tasks);
};

int main(int argc, char **argv) {
#ifdef DEBUG
  printf(_PRINT_RED("Warning: This program is running in debug mode.\n"));
#endif

  curl_global_init(CURL_GLOBAL_ALL);

  print_about();

  tasks = generate_tasks(argc, argv);
  assert_not_null(tasks);

  ARGUMENTS cli_args;
  parse_cli_arguments(argc, argv, &cli_args);

  run_tasks(&cli_args, tasks);

  return 0;
};