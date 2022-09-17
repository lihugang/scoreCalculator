
#include "../arguments.h"
#include "../colorful/colorful.h"
#include "../debug/macro.h"
#include "../globalVars.c"

extern unsigned char input_file_buffer[INPUT_FILE_MAX_SIZE];

void read_input_file(_IN ARGUMENTS* args) {
  assert_not_null(args);

  FILE* read_fp = fopen(args->filepath, "r");
  if (read_fp == NULL) throw_err("Cannot open input file");

  size_t read_size = fread(input_file_buffer, 1, (INPUT_FILE_MAX_SIZE) - 1, read_fp);
  input_file_buffer[read_size] = '\0';  // end of string
};