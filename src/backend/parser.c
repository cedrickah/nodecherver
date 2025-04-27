#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "parser.h"
#include "rio.h"
#include "request.h"

void url_decode(char* src, char* dest, int max) {
    char *p = src;
    char code[3] = { 0 };
    while(*p && --max) {
        if(*p == '%') {
            memcpy(code, ++p, 2);
            *dest++ = (char)strtoul(code, NULL, 16);
            p += 2;
        } else {
            *dest++ = *p++;
        }
    }
    *dest = '\0';
}

void parse_request(int connfd, request *req){
    rio_t rio;
    char buf[MAXLINE], method[MAXLINE], url[MAXLINE];
    req->offset = 0;
    req->end = 0;           

    rio_readinitb(&rio, connfd);
    rio_readlineb(&rio, buf, MAXLINE);
    sscanf(buf, "%s %s", method, url);
    memcpy(req->method, method, strlen(method));
    while(buf[0] != '\n' && buf[1] != '\n') {
        rio_readlineb(&rio, buf, MAXLINE);
        if(buf[0] == 'R' && buf[1] == 'a' && buf[2] == 'n'){
            sscanf(buf, "Range: bytes=%lu-%lu", &req->offset, &req->end);
            if( req->end != 0) req->end ++;
        }
    }
    if(url[0] != '/'){
        int length = strlen(url);
        for (int i = 0; i < length; ++ i) {
            if (url[i] == '?') {
                url[i] = '\0';
                break;
            }
        }
    }
    url_decode(url, req->url, MAXLINE);
} 
