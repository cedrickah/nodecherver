#ifndef _REQUEST_H_
#define _REQUEST_H_ 

#include <netinet/in.h>

typedef struct {
    char url[512];
    char method[512];
    off_t offset;
    size_t end;
} request;

extern request handle_request(int connfd, struct sockaddr_in *clientaddr);

#endif
