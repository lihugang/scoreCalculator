#pragma once

#ifndef _INCLUDE_FUNC_GENERATE_TASK_
#define _INCLUDE_FUNC_GENERATE_TASK_

#include "../arguments.h"
#include "../debug/macro.h"

#define MAX_TASK_COUNTS 1024
#define MAX_TASK_DESCRIPTION_LEN 256

typedef struct _task_ TASK;
typedef struct _task_list_ TASK_LIST;
_OUT TASK_LIST* generate_tasks(_IN int cli_argc, _IN char** cli_argv);
static void init_list(_INOUT TASK_LIST* list);
static void add_task_to_list(_INOUT TASK_LIST* tasks,
                             _IN void (*function)(ARGUMENTS* args),
                             _IN const char* description);
static void arrange_tasks(_INOUT TASK_LIST* tasks);

#include "generate_task.c"

#endif