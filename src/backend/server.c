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
#include "request.h"
#include "response.h"
#include "server.h"

void slisten(server *serv, int port, void (*handler)(request, response)){
    const int listenfd = open_listenfd(serv->fd, port);

    if(listenfd == -1){
        fprintf(stderr, "Cannot start server\n");
        exit(1); 
    }
   
    while(1){
        struct sockaddr_in clientaddr;
        
        const int connfd = connect_outfd(listenfd, clientaddr);

        if (connfd == -1) {
            fprintf(stderr, "Cannot accept connection\n");
        }
        
        request req = handle_request(connfd, &clientaddr);
        response res;
        res.fd = connfd;
        handle_response(req, res, handler);
        close(connfd);
    }
}
