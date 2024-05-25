# ifndef _BALANCER_H_
# define _BALANCER_H_

#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <linux/filter.h>
#include <signal.h>
#include <unistd.h>

/* Function to use for balancing load for udp protocol*/
void udpLoadBalancer(char* servicIp, int port, unsigned int groupSize);

/* Function to use for balancing load for tcp protocol*/
void tcpLoadBalancer(void);

#endif