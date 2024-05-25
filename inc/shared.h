#ifndef _LB_SHARED_H_
#define _LB_SHARED_H_

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <arpa/inet.h>
#include <string.h>
#include <signal.h>
#include "pthread.h"
#include <netdb.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <netinet/in.h>
#include <string.h>
#include <linux/limits.h>
#include "logger.h"
#include "memory.h"
#include "codes.h"

#ifndef LB_STR_LEN
#define LB_STR_LEN(s) strlen(s)
#endif

typedef struct {
	int len;
	char *s;
}_str_;
typedef _str_ str;

#endif /* _LB_SHARED_H_ */
