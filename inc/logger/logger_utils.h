#ifndef _LB_LOGGER_UTILS_H_
#define _LB_LOGGER_UTILS_H_

# include <stdarg.h>
# define _GNU_SOURCE
# include <stdio.h>
# include <stdlib.h>
# include <time.h>
# include <fcntl.h>
# include <string.h>
# include <unistd.h>

/*
** Macro to get the basename of the __FILE__ macro.
*/

# define __FILENAME__	\
	(strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)

// vars
extern int g_log_fd;
extern int g_log_lvl;

// functions
int logger_init_open_file(char *log_file);
void logger_fatal(int fd, char *file, int line, const char *fmt, ...);
void logger_error(int fd, char *file, int line, const char *fmt, ...);
void logger_warn(int fd, char *file, int line, const char *fmt, ...);
void logger_success(int fd, char *file, int line, const char *fmt, ...);
void logger_info(int fd, char *file, int line, const char *fmt, ...);
void logger_debug(int fd, char *file, int line, const char *fmt, ...);
void logger_trace(int fd, char *file, int line, const char *fmt, ...);
char *logger_get_time(void);

#endif /* _LB_LOGGER_UTILS_H_ */
