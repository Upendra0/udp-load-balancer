#include "logger.h"
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <limits.h>

void logger_default(int line, const char *fmt, ...) {

    va_list	lst;
	char	*time1;
	char	*out_info;
	char	*out_mesg;
    int fd;
   // Create or open log file in append mode
    time_t t = time(NULL);
    struct tm *currentTime = localtime(&t);
    char cwd[PATH_MAX];
    if (getcwd(cwd, sizeof(cwd)) == NULL)
    {
        log_error("Not able to get current working directory.\n");
    }
    char logFileName[20];
    strftime(logFileName, sizeof(logFileName), "/log_%Y%m%d.log", currentTime);
    strcat(cwd, logFileName);

    // Open the log file in append mode
    FILE *logFile = fopen(cwd, "a");
    if (logFile == NULL)
    {
        log_error("Failed to open log file: %s\n", cwd);
        return;
    }

    fd = fileno(logFile);
    if(fd==-1)
    {
        log_error("Not able to get file descriptor for log default file.\n");
    }

    // Write the message to the log file
    time1 = logger_get_time();
	asprintf(&out_info, "[ %s ] (l.%3d) %-20.20s -> ", time1, line, logFileName);

	va_start(lst, fmt);
	vasprintf(&out_mesg, fmt, lst);
	va_end(lst);

	dprintf(fd, "\033[0m%s%s\033[0m\n", out_info, out_mesg);

	free(out_info);
	free(out_mesg);
	free(time1);
    fclose(logFile);
}