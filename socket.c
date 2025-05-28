#include "socket.h"

#include <stdio.h>
#include <unistd.h>

int readn(int fd, char* buf, int count) {
    int nleft = count;
    int nread = 0;
    char* pbuf = buf;

    while (nleft > 0) {
        nread = read(fd, pbuf, nleft);

        if (nread == -1) {
            perror("read");
            return -1;
        } else if (nread == 0) {
            return count - nleft;
        }

        nleft -= nread;
        pbuf += nread;
    }

    return count;
}

int writen(int fd, char* buf, int count) {
    int nleft = count;
    int nwrite = 0;
    char* pbuf = buf;

    while (nleft > 0) {
        nwrite = write(fd, pbuf, nleft);

        if (nwrite == -1) {
            perror("write");
            return -1;
        } else if (nwrite == 0) {
            continue;
        }

        nleft -= nwrite;
        pbuf += nwrite;
    }

    return count;
}
