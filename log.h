#ifndef LOG_H
#define LOG_H

#include <stdarg.h>
#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif

#define LOG_STYLE_BOLD      "\x1b[1m"
#define LOG_STYLE_UNDERLINE "\x1b[4m"
#define LOG_STYLE_RESET     "\x1b[0m"

#define LOG_COLOR_RED    "\x1b[31m"
#define LOG_COLOR_GREEN  "\x1b[32m"
#define LOG_COLOR_YELLOW "\x1b[33m"
#define LOG_COLOR_BLUE   "\x1b[34m"
#define LOG_COLOR_CYAN   "\x1b[36m"

#define LOG_LEVEL_COUNT 5

typedef enum {
  LOG_LEVEL_TRACE = 0,
  LOG_LEVEL_DEBUG,
  LOG_LEVEL_INFO,
  LOG_LEVEL_WARNING,
  LOG_LEVEL_ERROR,
} LogLevel;

static const char *LEVEL_NAME[LOG_LEVEL_COUNT] = {"TRACE", "DEBUG", "INFO ",
                                                  "WARN ", "ERROR"};

static const char *LEVEL_COLOR[LOG_LEVEL_COUNT] = {
    LOG_COLOR_CYAN, LOG_COLOR_BLUE, LOG_COLOR_GREEN, LOG_COLOR_YELLOW,
    LOG_COLOR_RED};

static LogLevel current_log_level = LOG_LEVEL_TRACE;

/**
 * @brief Sets the current logging level.
 *
 * Messages with a level lower than the current level will be ignored.
 *
 * @param level The desired log level.
 */
static inline void set_log_level(LogLevel level) {
  if (level >= LOG_LEVEL_TRACE && level < LOG_LEVEL_COUNT) {
    current_log_level = level;
  }
}

/**
 * @brief Retrieves the current logging level.
 *
 * @return The current log level.
 */
static inline LogLevel get_log_level(void) { return current_log_level; }

/**
 * @brief Internal function to log a message with a specific log level.
 *
 * @param level  The severity level of the log message.
 * @param format The format string (printf-style).
 * @param ...    Variable arguments corresponding to the format string.
 */
static inline void log_message(LogLevel level, const char *format, ...) {
  if (level < current_log_level) {
    return;
  }

  const char *name   = LEVEL_NAME[level];
  const char *color  = LEVEL_COLOR[level];
  FILE       *output = (level == LOG_LEVEL_ERROR) ? stderr : stdout;

  va_list args;
  va_start(args, format);

  if (level == LOG_LEVEL_ERROR) {
    fprintf(output, "[%s%s%s%s] ", LOG_STYLE_BOLD, color, name,
            LOG_STYLE_RESET);
  } else {
    fprintf(output, "[%s%s%s] ", color, name, LOG_STYLE_RESET);
  }

  vfprintf(output, format, args);
  fprintf(output, "\n");

  va_end(args);
}

#define trace(...)   log_message(LOG_LEVEL_TRACE, __VA_ARGS__)
#define debug(...)   log_message(LOG_LEVEL_DEBUG, __VA_ARGS__)
#define info(...)    log_message(LOG_LEVEL_INFO, __VA_ARGS__)
#define warning(...) log_message(LOG_LEVEL_WARNING, __VA_ARGS__)
#define error(...)   log_message(LOG_LEVEL_ERROR, __VA_ARGS__)

#ifdef __cplusplus
}
#endif

#endif // LOG_H
