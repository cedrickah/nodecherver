#include <signal.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "response.h"
#include "request.h"
#include "rio.h"

status_map http_res_status [] = {
    {200, "OK"},
    {404, "Not Found"},
    {0, NULL},
};

char* get_status_msg(int code){
    status_map *status = http_res_status;
    while(status->code){
        if(status->code == code){
            return status->message;
        }else{
        }
        status++;
    }
    return "";
}

void write_head(response *res, int code){
    char buf[1024];
    char *msg = get_status_msg(code);
    
    sprintf(buf, "HTTP/1.1 %d %s\r\n", code, msg);
    sprintf(buf + strlen(buf),
            "Content-length: %d\r\n\r\n", 0);
    rio_write(res->fd, buf, strlen(buf));
}

void handle_response(request req, response res, void (*handler)(request, response)){
    res.write_head = &write_head;
    handler(req, res);
}
