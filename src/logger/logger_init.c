#include "shared.h"
#include "logger.h"

int g_log_fd = -1;
int g_log_lvl = -1;

int logger_init(int level, char *log_file) {
	int ret = LB_ERROR;

	if ((ret = logger_init_open_file(log_file)) < 0)
		return (ret);
	g_log_lvl = D_OFF;
	if (level >= D_FATAL && level <= D_TRACE)
	{
		g_log_lvl = level;
		dprintf(g_log_fd, "\n\033[32m>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> \033[0m");
		dprintf(g_log_fd, "\033[32mNEW INSTANCE OF THE APPLICATION\033[0m");
		dprintf(g_log_fd, "\033[32m <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<\033[0m\n\n");
	}
	return LB_SUCCESS;
}
