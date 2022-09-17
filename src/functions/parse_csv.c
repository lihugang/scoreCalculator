#include <stdint.h>

#include "../arguments.h"
#include "../colorful/colorful.h"
#include "../debug/macro.h"
#include "../globalVars.c"

extern unsigned char* csv_data[CSV_MAX_ROWS][CSV_MAX_COLS];
extern unsigned char input_file_buffer[INPUT_FILE_MAX_SIZE];
extern unsigned char csv_title[TITLE_MAX_LEN];

void parse_csv(_IN ARGUMENTS* args) {
  assert_not_null(args);

  for (size_t i = 0; i < CSV_MAX_ROWS; ++i)
    for (size_t j = 0; j < CSV_MAX_COLS; ++j) csv_data[i][j] = NULL;
  // clear data map

  int file_length = strlen((char*)input_file_buffer);
  debug_int(file_length);
  size_t first_line_length, column_pos;

  find_char(input_file_buffer, file_length, '\n', first_line_length);
  find_nchar(input_file_buffer, first_line_length, ',', column_pos);

  strncpy((char*)csv_title, input_file_buffer + column_pos, first_line_length);
  // substr string from the first not column postion to the end of this line

  find_char(csv_title, strlen(csv_title), ',', column_pos);
  if (column_pos != -1)            // has matches
    csv_title[column_pos] = '\0';  // remove the ending columns

  debug_str(csv_title);

  int currentCursor = first_line_length + 1;
  // parse csv for each row
  uint16_t csv_row = 0u, csv_col = 0u;

  while (currentCursor < file_length) {
    debug_uint(currentCursor);

    int line_len, first_column_pos = 0;
    find_char_with_start_pos(input_file_buffer, file_length, '\n', line_len,
                             currentCursor);
    if (line_len == -1) line_len = file_length;
    while (first_column_pos < line_len) {
      find_char_with_start_pos(input_file_buffer, file_length, ',',
                               first_column_pos, currentCursor);
      if (first_column_pos == -1) first_column_pos = line_len;
      first_column_pos = _min(first_column_pos, line_len);

      debug("Field in %d-%d", currentCursor, first_column_pos);

      alloc_memory_with_check(csv_data[csv_row][csv_col],
                              sizeof(char) * ONE_FIELD_MAX_LEN);
      if ((first_column_pos - currentCursor) >= ONE_FIELD_MAX_LEN)
        throw_err("Field in %d-%d is too large", currentCursor,
                  first_column_pos);
      strncpy((char*)(csv_data[csv_row][csv_col]),
              input_file_buffer + currentCursor,
              first_column_pos - currentCursor);
      currentCursor = first_column_pos + 1;
      csv_col++;
      if (csv_col >= CSV_MAX_COLS) throw_err("Too more columns");
    };
    csv_row++;
    if (csv_row >= CSV_MAX_ROWS) throw_err("Too more rows");
    csv_col = 0u;
    currentCursor = line_len + 1;
  };

  debug("Sorting rows");
  // due to some errors, `qsort` function will cause Segmentation fault, i use
  // bubble sort instead

  for (int i = 1; i < csv_row; ++i)
    for (int j = i + 1; j < csv_row; ++j) {
      unsigned char tmp[ONE_FIELD_MAX_LEN];
      assert_not_null(csv_data[i][0]);
      assert_not_null(csv_data[j][0]);
      if (atoi(csv_data[i][0]) > atoi(csv_data[j][0])) {
        for (int k = 0;; ++k) {
          if (csv_data[i][k] == NULL) break;
          if (csv_data[j][k] == NULL) break;
          debug("%d %d %d %s %s", i, j, k, csv_data[i][k], csv_data[j][k]);
          strcpy(tmp, csv_data[i][k]);
          strcpy(csv_data[i][k], csv_data[j][k]);
          strcpy(csv_data[j][k], tmp);
        };
      };
    };
};