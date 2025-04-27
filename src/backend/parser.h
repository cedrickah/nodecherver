#ifndef _PARSER_H_
#define _PARSER_H_ 

#include "request.h"

#define MAXLINE 1024

void url_decode(char* src, char* dest, int max);

extern void parse_request(int connfd, request *req);

#endif
