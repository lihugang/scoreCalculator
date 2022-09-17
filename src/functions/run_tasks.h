#pragma once
#ifndef _INC_RUN_TASK
#define _INC_RUN_TASK
#include "../debug/macro.h"
#include "../arguments.h"
#include "generate_task.h"
void run_tasks(_IN ARGUMENTS * args, _IN TASK_LIST * tasks);
#include "run_tasks.c"
#endif