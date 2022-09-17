#include <math.h>
#include <string.h>

#include "../arguments.h"
#include "../colorful/colorful.h"
#include "../debug/macro.h"
#include "../globalVars.c"

extern SCORE scores[SEAT_MAX_COLS];
extern int global_seatTable[SEAT_MAX_COLS][SEAT_MAX_ROWS];
extern unsigned char csv_title[TITLE_MAX_LEN];
extern unsigned char* csv_data[CSV_MAX_ROWS][CSV_MAX_COLS];

char output_path[8192] = {'\0'};  // output path

void output_to_txt(_IN ARGUMENTS* args) {
  for (unsigned int i = 0; i < args->options_len; ++i) {
    if (strlen(args->options[i]) > 7 && args->options[i][0] == 'o' &&
        args->options[i][1] == 'u' && args->options[i][2] == 't' &&
        args->options[i][3] == 'p' && args->options[i][4] == 'u' &&
        args->options[i][5] == 't' && args->options[i][6] == '=') {
      strncpy(output_path, args->options[i] + 7, 8191);  // copy output path
    };
  };
  if (output_path[0] == '\0')
    strcpy(output_path, "result.txt");  // default print to result.txt
  debug_str(output_path);

  FILE* write_fp = fopen(output_path, "w");
  assert_not_null(write_fp);

  fprintf(write_fp, "%s\n", (char*)csv_title);  // print title

  // sort
  int group_count = SEAT_MAX_COLS;
  for (int i = 0; i < SEAT_MAX_COLS; i++)
    if (abs(scores[i].score - 0.0) < 1e-3) {
      group_count = i;
      break;
    };
  // get the count of groups

  for (int i = 0; i < group_count; ++i)
    for (int j = i + 1; j < group_count; ++j) {
      if (scores[i].score < scores[j].score) {
        int tmp_id;
        float tmp_score;

        tmp_id = scores[i].id;
        scores[i].id = scores[j].id;
        scores[j].id = tmp_id;

        tmp_score = scores[i].score;
        scores[i].score = scores[j].score;
        scores[j].score = tmp_score;
      };
    };

  for (int i = 0; i < group_count; ++i) {
    // write to txt
    fprintf(write_fp, "第%d名 第%d组 总分%.1f分 ", i + 1, scores[i].id,
            scores[i].score);
    printf(_PRINT_MAGENTA("第") _PRINT_CYAN("%d") _PRINT_MAGENTA("名 第")
               _PRINT_CYAN("%d") _PRINT_MAGENTA("组 总分") _PRINT_CYAN("%.1f")
                   _PRINT_MAGENTA("分 "),
           i + 1, scores[i].id, scores[i].score);
    for (int j = 0;; ++j) {
      if (global_seatTable[scores[i].id - 1][j] == 0) break;
      int id = global_seatTable[scores[i].id - 1][j];

      const char* name = csv_data[id][1];  // number name ...scores

      fprintf(write_fp, "%s ", name);
      printf(_PRINT_YELLOW("%s "), name);
    };
    fprintf(write_fp, "\n");
    printf("\n");
  };
  fclose(write_fp);
};