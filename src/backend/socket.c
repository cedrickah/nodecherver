#include <arpa/inet.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include "socket.h"

ssize_t init_listenfd(){
    const int optval=1;
    int listenfd = socket(AF_INET, SOCK_STREAM, 0);
        
    if(listenfd == -1){
        return -1; 
    }
    
    if (setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, (const void *)&optval , sizeof(int)) < 0){
        return -1; 
    }
        
    return listenfd;
} 

ssize_t open_listenfd(int listenfd, int port){
    struct sockaddr_in serveraddr;
    
    serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons((unsigned short)port);
    
    if(bind(listenfd,  (struct sockaddr *)&serveraddr, sizeof(serveraddr)) == -1){
        return -1; 
    }
    
    if (listen(listenfd, LISTENQ) == -1) {
        return -1; 
    } 
        
    return listenfd;
}

ssize_t connect_outfd(int listenfd, struct sockaddr_in clientaddr){    
    socklen_t cliaddrlen = sizeof(clientaddr);
    
    int connfd = accept(listenfd, (struct sockaddr *)&clientaddr, &cliaddrlen);
    
    if (connfd == -1) {
        return -1; 
    }
    
    return connfd;
}
