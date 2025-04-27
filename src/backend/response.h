#ifndef _RESPONSE_H_
#define _RESPONSE_H_ 

#include "request.h"

typedef struct {
    int code;
    char *message;
} status_map;

typedef struct {
    void (*write_head)(void *self, int status);
    int fd;
} response;

char* get_status_msg(int code);

void write_head(response *res, int code);

extern void handle_response(request req, response res, void (*handler)(request, response));

#endif
