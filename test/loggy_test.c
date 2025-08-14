#include "loggy.h"
#include <assert.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>

void test_log(LogLevel_t level, const char *msg) {
  char buf[256] = {0};
  FILE *mem = fmemopen(buf, sizeof(buf), "w");
  assert(mem && "Failed to open memory stream");

  Loggy_t lgy = loggy_init(mem, mem, level);
  assert(lgy.file && "Failed to open memory stream");

  switch (level) {
  case LOGGY_DEBUG:
    loggy_debug(&lgy, "%s", msg);
    break;
  case LOGGY_INFO:
    loggy_info(&lgy, "%s", msg);
    break;
  case LOGGY_WARN:
    loggy_warn(&lgy, "%s", msg);
    break;
  case LOGGY_ERROR:
    loggy_error(&lgy, "%s", msg);
    break;
  }

  fflush(mem);

  // --- Checks with printed insight ---
  printf("Testing log level: %s\n", log_level_str[level]);

  printf("Checking timestamp format... ");
  assert(buf[0] == '[' && "log output missing opening timestamp bracket");
  assert(strchr(buf, ']') && "log output missing closing timestamp bracket");
  printf("OK\n");

  printf("Checking colored log level... ");
  assert(strstr(buf, log_level_str[level]) &&
         "log output missing correct colored log level");
  printf("OK\n");

  printf("Checking message content... ");
  assert(strstr(buf, msg) && "log output missing message");
  printf("OK\n");

  printf("Captured log: %s\n\n", buf);

  fclose(mem);
}

void test_set_level_runtime() {
  char buf[512] = {0};
  FILE *mem = fmemopen(buf, sizeof(buf), "w");
  assert(mem && "Failed to open memory stream");

  Loggy_t lgy = loggy_init(mem, mem, LOGGY_WARN);
  assert(lgy.file && "Failed to open memory stream");

  printf("Testing initial log level: WARN\n");
  loggy_debug(&lgy, "Debug message");
  loggy_info(&lgy, "Info message");
  loggy_warn(&lgy, "Warn message");
  loggy_error(&lgy, "Error message");

  fflush(mem);

  printf("Checking which messages appear at WARN level...\n");
  assert(!strstr(buf, "Debug message"));
  printf("DEBUG message correctly filtered out\n");
  assert(!strstr(buf, "Info message"));
  printf("INFO message correctly filtered out\n");
  assert(strstr(buf, "Warn message"));
  printf("WARN message correctly logged\n");
  assert(strstr(buf, "Error message"));
  printf("ERROR message correctly logged\n");

  // Clear buffer for next phase
  rewind(mem);
  memset(buf, 0, sizeof(buf));

  printf("\nChanging log level to DEBUG\n");
  loggy_set_level(&lgy, LOGGY_DEBUG);

  printf("Logging all messages at DEBUG level...\n");
  loggy_debug(&lgy, "Debug message");
  loggy_info(&lgy, "Info message");
  loggy_warn(&lgy, "Warn message");
  loggy_error(&lgy, "Error message");

  fflush(mem);

  assert(strstr(buf, "Debug message"));
  printf("DEBUG message now appears\n");
  assert(strstr(buf, "Info message"));
  printf("INFO message now appears\n");
  assert(strstr(buf, "Warn message"));
  printf("WARN message still appears\n");
  assert(strstr(buf, "Error message"));
  printf("ERROR message still appears\n");

  fclose(mem);

  printf("\nSet level runtime test passed\n");
}

int main() {
  test_log(LOGGY_DEBUG, "Debug message");
  test_log(LOGGY_INFO, "Info message");
  test_log(LOGGY_WARN, "Warn message");
  test_log(LOGGY_ERROR, "Error message");
  test_set_level_runtime();

  printf("All tests passed\n");
  return 0;
}
