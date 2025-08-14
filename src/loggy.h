#include <stdio.h>

typedef enum {
  LOGGY_DEBUG,
  LOGGY_INFO,
  LOGGY_WARN,
  LOGGY_ERROR,
} LogLevel_t;

#define RESET "\x1b[0m]"
#define RED "[\x1b[31m"
#define YELLOW "[\x1b[33m"
#define GREEN "[\x1b[32m"
#define CYAN "[\x1b[36m"
static const char *log_level_str[] = {[LOGGY_DEBUG] = CYAN "DEBUG" RESET,
                                      [LOGGY_INFO] = GREEN "INFO" RESET,
                                      [LOGGY_WARN] = YELLOW "WARN" RESET,
                                      [LOGGY_ERROR] = RED "ERROR" RESET};

typedef struct {
  FILE *file;
  FILE *error_file;
  LogLevel_t min_lvl;
} Loggy_t;

Loggy_t loggy_init(FILE *out, FILE *error_file, LogLevel_t lvl);

int loggy_set_level(Loggy_t *lgy, LogLevel_t lvl);

int loggy_debug(Loggy_t *lgy, const char *fmt, ...);
int loggy_info(Loggy_t *lgy, const char *fmt, ...);
int loggy_warn(Loggy_t *lgy, const char *fmt, ...);
int loggy_error(Loggy_t *lgy, const char *fmt, ...);
