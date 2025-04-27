#ifndef _HTTP_H_
#define _HTTP_H_ 

#include "server.h"

void init_server(server *serv, int listenfd);

extern server create_server();

#endif
