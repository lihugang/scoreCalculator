#ifndef _INC_GVARS_
#define _INC_GVARS_

#include <stdint.h>
#include <stdio.h>

#define SEAT_MAX_COLS 100
#define SEAT_MAX_ROWS 100

#define INPUT_FILE_MAX_SIZE 1024 * 1024  // 1m

#define TITLE_MAX_LEN 1024
#define CSV_MAX_ROWS 1024
#define CSV_MAX_COLS 15

#define ONE_FIELD_MAX_LEN 32

typedef struct _score {
  uint8_t id;
  float score;
} SCORE;

int global_seatTable[SEAT_MAX_COLS][SEAT_MAX_ROWS] = {0};
SCORE scores[SEAT_MAX_COLS];
unsigned char input_file_buffer[INPUT_FILE_MAX_SIZE] = {0};

unsigned char* csv_data[CSV_MAX_ROWS][CSV_MAX_COLS] = {NULL};

unsigned char csv_title[TITLE_MAX_LEN] = {0};

const char* seat_table_save_path = ".seat-table";
char* output_file_save_path = "result.txt";

#endif