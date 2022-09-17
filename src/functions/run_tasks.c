#include <stdio.h>
#include <time.h>

#include "../arguments.h"
#include "../debug/macro.h"
#include "generate_task.h"
void run_tasks(_IN ARGUMENTS* args, _IN TASK_LIST* tasks) {
  assert_not_null(args);
  assert_not_null(tasks);

  uint16_t task_counts = tasks->task_counts;
  clock_t start_clock, end_clock;
  printf(_PRINT_CYAN("Counts of tasks: "));
  printf(_PRINT_YELLOW("%u"), tasks->task_counts);
  printf("\n");
  
  for (uint16_t i = 0; i < task_counts; ++i) {
    printf(_PRINT_CYAN("Running task "));
    printf(_PRINT_YELLOW("%u "), ((tasks->tasks)[i]).task_id);
    printf(_COLORFUL_WITHOUT_BKG(_DISPLAY_COMP, _FCOLOR_MAGENTA, "%s\n"),
           ((tasks->tasks)[i]).description);
    start_clock = clock();

    ((tasks->tasks)[i]).call_func(args);

    end_clock = clock();
    printf(_PRINT_CYAN("Finished running task "));
    printf(_PRINT_YELLOW("%u"), ((tasks->tasks)[i]).task_id);
    printf(_PRINT_CYAN(", using time "));
    printf(_PRINT_YELLOW("%d"),
           ((end_clock - start_clock) * 1000 / CLOCKS_PER_SEC));
    printf(_PRINT_CYAN(" ms\n"));
  };
};