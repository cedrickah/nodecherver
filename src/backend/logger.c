#include <stdio.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netinet/tcp.h>
#include <sys/socket.h>
#include "logger.h"
#include "request.h"

void log_info(char *str, int connfd){
    printf(str, connfd);
}

void log_access(int status, struct sockaddr_in *clientaddr, request *req){
    printf("%s:%d %d - %s\n", inet_ntoa(clientaddr->sin_addr),
           ntohs(clientaddr->sin_port), status, req->url);
}
