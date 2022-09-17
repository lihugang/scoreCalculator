#pragma once
#include "generate_task.h"

#include <stdint.h>

#include "../arguments.h"
#include "../colorful/colorful.h"
#include "../debug/macro.h"
#include "subTasks.h"

typedef struct _task_ {
  uint16_t task_id;
  void (*call_func)(ARGUMENTS* args);
  char description[MAX_TASK_DESCRIPTION_LEN];
} TASK;

typedef struct _task_list_ {
  int task_counts;
  TASK tasks[MAX_TASK_COUNTS];
} TASK_LIST;

static void init_list(_INOUT TASK_LIST* list) {
  assert_not_null(list);
  list->task_counts = 0;
  for (int i = 0; i < MAX_TASK_COUNTS; ++i) {
    ((list->tasks)[i]).task_id = 0;
    ((list->tasks)[i]).call_func = NULL;
  };
};

inline static void add_task_to_list(_INOUT TASK_LIST* tasks,
                                    _IN void (*function)(ARGUMENTS* args),
                                    _IN const char* description) {
  assert_not_null(tasks);
  assert_not_null(function);

  uint16_t task_id = tasks->task_counts;

  if (task_id >= MAX_TASK_COUNTS) throw_err("Too many tasks");
  ++(tasks->task_counts);

  ((tasks->tasks)[task_id]).task_id = task_id;
  ((tasks->tasks)[task_id]).call_func = function;
  strcpy(((tasks->tasks)[task_id]).description, description);
};

static void arrange_tasks(_INOUT TASK_LIST* tasks) {
  assert_not_null(tasks);

  for (uint16_t i = 0; i < tasks->task_counts; ++i)
    ((tasks->tasks)[i]).task_id = i + 1;
};

_OUT TASK_LIST* generate_tasks(_IN int cli_argc, _IN char** cli_argv) {
  printf(_PRINT_CYAN("Generating tasks...\n"));

  ARGUMENTS cli_args;
  parse_cli_arguments(cli_argc, cli_argv, &cli_args);

  debug("Filepath: %s", cli_args.filepath);

  TASK_LIST* tasks;
  alloc_memory_with_check(tasks, sizeof(TASK_LIST));

  init_list(tasks);

#ifndef NODOWNLOADSEATTABLE
  add_task_to_list(tasks, download_seat_table, "Downloading seat table");
#endif
  add_task_to_list(tasks, process_seat_table, "Processing seat table data");
  add_task_to_list(tasks, read_input_file, "Reading input file");
  add_task_to_list(tasks, parse_csv, "Parse CSV file");
  add_task_to_list(tasks, calc_score, "Calculating scores for each group");
#ifndef NOCOLLECTFILE
  add_task_to_list(tasks, collect_file, "Collecting the input file");
#endif
  add_task_to_list(tasks, output_to_txt, "Writing results to output file");

  arrange_tasks(tasks);

  return tasks;
};