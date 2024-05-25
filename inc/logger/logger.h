# ifndef _LB_LOGGER_H_
# define _LB_LOGGER_H_

# include "logger_utils.h"

// log levels
# define D_OFF			0
# define D_FATAL		1
# define D_ERROR		2
# define D_WARN			3
# define D_SUCCESS		4
# define D_INFO			5
# define D_DEBUG		6
# define D_TRACE		7

/*
** Functions to use for display log messages.
*/

# define log_default(...)	\
	logger_default(g_log_fd, __FILENAME__, __LINE__, __VA_ARGS__)

#define log_fatal(...)		\
	logger_fatal(g_log_fd, __FILENAME__, __LINE__, __VA_ARGS__)

#define log_error(...)		\
	logger_error(g_log_fd, __FILENAME__, __LINE__, __VA_ARGS__)

#define log_warn(...)		\
	logger_warn(g_log_fd, __FILENAME__, __LINE__, __VA_ARGS__)

#define log_success(...)	\
	logger_success(g_log_fd, __FILENAME__, __LINE__, __VA_ARGS__)

#define log_info(...)		\
	logger_info(g_log_fd, __FILENAME__, __LINE__, __VA_ARGS__)

#define log_debug(...)		\
	logger_debug(g_log_fd, __FILENAME__, __LINE__, __VA_ARGS__)

#define log_trace(...)		\
	logger_trace(g_log_fd, __FILENAME__, __LINE__, __VA_ARGS__)

int logger_init(int level, char *log_file);
int logger_close(void);

#endif /* _LB_LOGGER_H_ */
