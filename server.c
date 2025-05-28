#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "socket.h"

void send_msg(int fd, char* data, int length) {
    char* buf = (char*)malloc(length + sizeof(int));
    int netlen = htons(length);

    memcpy(buf, &netlen, sizeof(int));
    memcpy(buf + sizeof(int), data, length);

    writen(fd, buf, length + sizeof(int));
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
    addr.sin_addr.s_addr = INADDR_ANY;

    int ret = bind(fd, (struct sockaddr *)&addr, sizeof(addr));

    if (ret == -1) {
        perror("bind");
        exit(0);
    }

    ret = listen(fd, 128);

    if (ret == -1) {
        perror("listen");
        exit(0);
    }

    struct sockaddr_in addr_client;
    int len = sizeof(addr_client);
    int cfd = accept(fd, (struct sockaddr *)&addr_client, &len);

    if (cfd == -1) {
        perror("accept");
        exit(0);
    }

    const char *buf[] = {"The quick brown fox jumps over the lazy dog\n",
                         "She sells seashells by the seashore\n",
                         "How much wood would a woodchuck chuck\n",
                         "If a woodchuck could chuck wood\n",
                         "All your base are belong to us\n",
                         "I think therefore I am\n",
                         "To be or not to be, that is the question\n",
                         "The rain in Spain stays mainly in the plain\n",
                         "In a hole in the ground there lived a hobbit\n",
                         "Call me Ishmael\n",
                         "Elementary, my dear Watson\n",
                         "It was the best of times, it was the worst of times\n",
                         "May the Force be with you\n",
                         "Houston, we have a problem\n",
                         "I'm gonna make him an offer he can't refuse\n",
                         "Here's looking at you, kid\n",
                         "You talking to me?\n",
                         "Life is like a box of chocolates\n",
                         "I'll be back\n",
                         "Why so serious?\n",
                         "I see dead people\n",
                         "Keep your friends close, but your enemies closer\n",
                         "Frankly, my dear, I don't give a damn\n",
                         "The only thing we have to fear is fear itself\n",
                         "That's one small step for man, one giant leap for mankind\n",
                         "You can't handle the truth!\n",
                         "I'm the king of the world!\n",
                         "Say hello to my little friend!\n",
                         "A wizard is never late, nor is he early\n",
                         "Just keep swimming\n",
                         "With great power comes great responsibility\n",
                         "It’s dangerous to go alone! Take this.\n",
                         "You shall not pass!\n",
                         "Winter is coming\n",
                         "I am the danger\n",
                         "This is the way\n",
                         "These aren't the droids you're looking for\n",
                         "I'm not superstitious, but I am a little stitious\n",
                         "I've made a huge mistake\n",
                         "Bears. Beets. Battlestar Galactica.\n",
                         "I'm in a glass case of emotion!\n",
                         "I drink and I know things\n",
                         "You know nothing, Jon Snow\n",
                         "I am Groot\n",
                         "Some people just want to watch the world burn\n",
                         "I'm vengeance\n",
                         "Because I'm Batman\n",
                         "Not all those who wander are lost\n",
                         "Time is an illusion, lunchtime doubly so\n",
                         "So long, and thanks for all the fish\n",
                         "It's a trap!\n",
                         "Welcome to the real world\n",
                         "The cake is a lie\n",
                         "War. War never changes.\n",
                         "Snake? Snake!? Snaaaake!\n",
                         "Finish him!\n",
                         "Hadouken!\n",
                         "The truth is out there\n"};


    int length = sizeof(buf) / sizeof(buf[0]);
    for (int i = 0; i < length; ++i) {
        send_msg(cfd, buf[i], strlen(buf[i]));
        usleep(1000 * 500);
    }

    printf("Data sent completely, any key to continue...\n");
    getchar();
    
    close(fd);
    close(cfd);

    return 0;
}