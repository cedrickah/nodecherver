#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netinet/tcp.h>
#include <sys/socket.h>
#include <unistd.h>
#include "socket.h"
#include "server.h"

void init_server (server *serv, int listenfd) {
    serv->fd = listenfd;
    serv->listen = &slisten;
}

server create_server (){
    const int fd = init_listenfd();

    if(fd == -1){
        fprintf(stderr, "Cannot create server\n");
        exit(1); 
    }
    server serv;
    init_server(&serv, fd);
    return serv;
}
