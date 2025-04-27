#include <signal.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "request.h"
#include "rio.h"
#include "logger.h"
#include "parser.h"

request handle_request(int connfd, struct sockaddr_in *clientaddr){
    log_info("Incoming request: fd is %d\n", connfd);
    request req;
    parse_request(connfd, &req);

    int status = 200;
    if(strcmp(req.url, "/") != 0){
        status = 404;
    }
    log_access(status, clientaddr, &req);
    return req;
}

