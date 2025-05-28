#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

int recv_msg(int fd, char** buf) {
    int netlen = 0;
    int ret = readn();
    int len = ntohs(netlen);

    printf("The length of data: %d\n", len);

    char* tmp = (char*)malloc(sizeof(len + 1));

    ret = readn();
    tmp[len] = '\0';

    *buf = tmp;

    return ret;
}

int main() {
    int fd = socket(AF_INET, SOCK_STREAM, 0);

    if (fd == -1) {
        perror("socket");
        exit(0);
    }

    struct sockaddr_in addr;

    addr.sin_family = AF_INET;
    addr.sin_port = htons(9999);
    
    inet_pton(AF_INET, "127.0.0.1", &addr.sin_addr.s_addr);

    int ret = connect(fd, (struct sockaddr*)&addr, sizeof(addr));

    if (ret == -1) {
        perror("connect");
        exit(0);
    }

    while (1) {
        char recv_buf[1024];

        memset(recv_buf, 0, sizeof(recv_buf));

        int ret = recv_msg(fd, recv_buf);

        if (ret == -1) {
            perror("read");
            break;
        } else if (ret == 0) {
            printf("Server disconnected...\n");
            break;
        } else {
            printf("Received data: %s\n", recv_buf);
        }

        printf("\n\n=========================\n\n");
        sleep(rand() % 5);
    }
    
    close(fd);

    return 0;
}