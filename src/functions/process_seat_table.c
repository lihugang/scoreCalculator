#include <stdint.h>
#include <stdio.h>

#include "../arguments.h"
#include "../debug/macro.h"
#include "../globalVars.c"

extern const char* seat_table_save_path;

extern int global_seatTable[SEAT_MAX_COLS][SEAT_MAX_ROWS];

void process_seat_table(_IN ARGUMENTS* args) {
  assert_not_null(args);
  ++(args->not_used_counters);
  FILE* read_fp = fopen(seat_table_save_path, "r");
  assert_not_null(read_fp);

  uint16_t currentRow = 0, currentColumn = 0;
  for (;;) {
    if (fscanf(read_fp, "%d", &(global_seatTable[currentColumn][currentRow])) <=
        0 /*read error*/) {
      // next row
      char tmp;
      if (fscanf(read_fp, "%c", &tmp) == EOF || tmp != 'n') {
        // end of file
        break;
      };
      currentColumn++;
      if (currentColumn >= SEAT_MAX_COLS)
        throw_err("Too much columns in seat table: %d", currentColumn);
      currentRow = 0;
      continue;
    };
    currentRow++;
    if (currentRow >= SEAT_MAX_ROWS)
      throw_err("Too many rows in seat table: %d", currentRow);
  };
  fclose(read_fp);
};