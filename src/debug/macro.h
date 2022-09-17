#pragma once

#ifndef _INC_MACROS_
#define _INC_MACROS_
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../colorful/colorful.h"

#ifndef _IN

#define _IN

#endif

#ifndef _OUT

#define _OUT

#endif

#ifndef _INOUT

#define _INOUT

#endif

// define int and out macro

#define throw_err(...)                      \
  {                                         \
    fprintf(stderr, _PRINT_RED("Error: ")); \
    fprintf(stderr, __VA_ARGS__);           \
    exit(0);                                \
  };

#define throw_cannot_alloc_memory_err() throw_err("Cannot allocate memory");
#define throw_null_pointer_err() \
  throw_err("Detect a null pointer exception in %s:%d");

// throw error macros

#define assert_not_null(ptr)                   \
  {                                            \
    if (ptr == NULL) throw_null_pointer_err(); \
  };
#define alloc_memory_with_check(ptr, size)            \
  {                                                   \
    ptr = malloc(size);                               \
    if (ptr == NULL) throw_cannot_alloc_memory_err(); \
    memset(ptr, 0, size);                             \
  };

// assert macros

#ifdef DEBUG
#define debug(...)                                  \
  {                                                 \
    printf("[DEBUG] [%s:%d] ", __FILE__, __LINE__); \
    printf(__VA_ARGS__);                            \
    printf("\n");                                   \
  };
#define debug_int(x) debug(#x " = %d", x)
#define debug_uint(x) debug(#x " = %u", x)
#define debug_float(x) debug(#x " = %f", x)
#define debug_char(x) debug(#x " = %c", x)
#define debug_long(x) debug(#x " = %ld", x)
#define debug_long_long(x) debug(#x " = %lld", x)
#define debug_u_long_long(x) debug(#x " = %llu", x)
#define debug_u_long(x) debug(#x " = %lu", x)
#define debug_ptr(x) debug(#x " = %p", x)
#define debug_str(x) debug(#x " = %s", x)
#else
#define debug(...)
#define debug_int(x)
#define debug_uint(x)
#define debug_float(x)
#define debug_char(x)
#define debug_long(x)
#define debug_long_long(x)
#define debug_u_long_long(x)
#define debug_u_long(x)
#define debug_ptr(x)
#define debug_str(x)

#endif
// debug logs

#define MAX_URL_SIZE 2048
#define MAX_DOMAIN_SIZE 128
#define MAX_TOKEN_SIZE 2048
#define MAX_AUTHORIZATION_HEADER_SIZE 256
#define MAX_RESPONSE_BUFFER_SIZE 1024 * 1024 * 4  // 4m
// macros for http requests

#define find_char_with_start_pos(str, str_len, ch, pos, start_pos) \
  {                                                                \
    size_t len = str_len;                                          \
    uint8_t isFind = 0;                                            \
    for (size_t i = start_pos; i < len; ++i)                       \
      if (str[i] == ch) {                                          \
        pos = i;                                                   \
        isFind = 1;                                                \
        break;                                                     \
      };                                                           \
    if (!isFind) pos = -1;                                         \
  };

#define find_char(str, str_len, ch, pos) \
  find_char_with_start_pos(str, str_len, ch, pos, 0)

#define find_nchar(str, str_len, ch, pos) \
  {                                       \
    size_t len = str_len;                 \
    uint8_t isFind = 0;                   \
    for (size_t i = 0; i < len; ++i)      \
      if (str[i] != ch) {                 \
        pos = i;                          \
        isFind = 1;                       \
        break;                            \
      };                                  \
    if (!isFind) pos = -1;                \
  };

#define _min(a, b) (((a) < (b)) ? (a) : (b))
#define _max(a, b) (((a) > (b)) ? (a) : (b))

// useful tools
#endif