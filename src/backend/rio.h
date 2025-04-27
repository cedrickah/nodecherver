#ifndef _RIO_H_
#define _RIO_H_ 

#define BUFLEN 1500
#define RIO_BUFSIZE 1024

typedef struct {
    int rio_fd;                 
    int rio_cnt;                
    char *rio_bufptr;           
    char rio_buf[RIO_BUFSIZE];  
} rio_t;

extern void rio_readinitb(rio_t *rp, int fd);

ssize_t rio_read(rio_t *rp, char *usrbuf, int n);

extern ssize_t rio_readlineb(rio_t *rp, void *usrbuf, int maxlen);

extern ssize_t rio_write(int fd, void *usrbuf, size_t n);

#endif


