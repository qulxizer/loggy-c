#include "loggy.h"
#include <bits/types/stack_t.h>
#include <stdarg.h>
#include <stdio.h>
#include <time.h>

Loggy_t loggy_init(FILE *out, LogLevel_t lvl) {
  Loggy_t lgy;
  lgy.file = out;
  lgy.min_lvl = lvl;

  return lgy;
}

int loggy_set_level(Loggy_t *lgy, LogLevel_t lvl) {
  if (!lgy) {
    return -1;
  }
  lgy->min_lvl = lvl;
  return 0;
}

static int loggy_global(Loggy_t *lgy, LogLevel_t lvl, const char *fmt,
                        va_list args) {
  if (!lgy || !lgy->file)
    return -1;
  if (lvl < lgy->min_lvl) {
    return 0;
  }
  const char *level = log_level_str[lvl];

  char timebuf[64];
  time_t t = time(NULL);
  struct tm *tm_info = localtime(&t);
  strftime(timebuf, sizeof(timebuf), "[%Y-%m-%d %H:%M:%S]", tm_info);
  fprintf(lgy->file, "%s %s ", timebuf, level);

  vfprintf(lgy->file, fmt, args);
  fprintf(lgy->file, "\n");
  return 0;
}

int loggy_debug(Loggy_t *lgy, const char *fmt, ...) {
  if (!lgy || !lgy->file)
    return -1;

  va_list args;
  va_start(args, fmt);
  int status = loggy_global(lgy, LOGGY_DEBUG, fmt, args);
  va_end(args);

  return 0;
}

int loggy_info(Loggy_t *lgy, const char *fmt, ...) {
  if (!lgy || !lgy->file)
    return -1;

  va_list args;
  va_start(args, fmt);
  int status = loggy_global(lgy, LOGGY_INFO, fmt, args);
  va_end(args);

  return status;
}

int loggy_warn(Loggy_t *lgy, const char *fmt, ...) {
  if (!lgy || !lgy->file)
    return -1;

  va_list args;
  va_start(args, fmt);
  int status = loggy_global(lgy, LOGGY_WARN, fmt, args);
  va_end(args);

  return status;
}
int loggy_error(Loggy_t *lgy, const char *fmt, ...) {
  if (!lgy || !lgy->file)
    return -1;

  va_list args;
  va_start(args, fmt);
  int status = loggy_global(lgy, LOGGY_ERROR, fmt, args);
  va_end(args);

  return status;
}
