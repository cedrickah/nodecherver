#ifndef _SOCKET_H_
#define _SOCKET_H_

#include <netinet/in.h>

#define LISTENQ  1024

extern ssize_t init_listenfd();

extern ssize_t open_listenfd(int listenfd, int port);

extern ssize_t connect_outfd(int listenfd, struct sockaddr_in clientaddr);

#endif
