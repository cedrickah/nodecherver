#ifndef _LOGGER_H_
#define _LOGGER_H_ 

#include "request.h"

extern void log_info(char *str, int connfd);

extern void log_access(int status, struct sockaddr_in *c_addr, request *req);

#endif
