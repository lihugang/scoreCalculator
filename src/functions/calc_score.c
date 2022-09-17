#include "../arguments.h"
#include "../colorful/colorful.h"
#include "../debug/macro.h"
#include "../globalVars.c"

extern unsigned char* csv_data[CSV_MAX_ROWS][CSV_MAX_COLS];
extern int global_seatTable[SEAT_MAX_COLS][SEAT_MAX_ROWS];
extern SCORE scores[SEAT_MAX_COLS];

/*
Require format:
<Title>
ID, NAME, CHINESE, MATH, ENGLISH, PHYSICS, POLITICS, HISTORY
1, xxx, xxx, xxx, xxx, xxx, xxx, xxx, xxx, xxx
*/

void calc_score(_IN ARGUMENTS* args) {
  assert_not_null(args);
  ++(args->not_used_counters);
  // the first record is
  // ID,NAME.................................................. read from the
  // second record

  for (int i = 0; i < SEAT_MAX_COLS; ++i) {
    scores[i].id = 0;
    scores[i].score = 0.0;
  };

  for (int i = 0; i < SEAT_MAX_COLS; ++i) {
    if (global_seatTable[i][0] == 0) break;
    for (int j = 0; j < SEAT_MAX_ROWS; ++j) {
      if (global_seatTable[i][j] == 0) break;
      int id = global_seatTable[i][j];
      debug_int(id);
      for (int k = 2; k < CSV_MAX_COLS; ++k) {
        // foreach his/her scores add to the group sum
        // the first is id, the second is name
        // read starts from the third
        debug_str(csv_data[id][k]);
        if (csv_data[id][k] == NULL) break;
        scores[i].score += atof((unsigned char*)csv_data[id][k]);
        debug_float(atof((unsigned char*)csv_data[id][k]));
      };
      scores[i].id = i + 1;
    };
    debug_float(scores[i].score);
  };
};