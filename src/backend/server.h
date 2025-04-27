#ifndef _SERVER_H_
#define _SERVER_H_

#include "request.h"
#include "response.h"

typedef struct {
    void (*listen)(void *self, int port, void (*handler)(request, response));
    int fd;
} server;

typedef void (*handler)(request req, response res);

extern void slisten (server *serv, int port, void (*handler)(request, response));

#endif
