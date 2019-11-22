#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include "server.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char **argv) {
    struct message msg;
    int fdpub, fdpriv;
    char currentline[LEN];

    int sum = 0;
    int last = 0;

    sprintf(msg.privfifo, "Fifo%d", getpid());
    if (mkfifo(msg.privfifo, S_IFIFO | 0666) == -1) {
        perror(msg.privfifo);
        exit(1);
    }
    if ((fdpub = open(PUBLIC_CHAN, O_WRONLY)) == -1) {
        perror(PUBLIC_CHAN);
        exit(2);
    }


    char string[LEN];

    while (fgets(string, LEN, stdin) != NULL) {
        strcpy(msg.string, string);
        write(fdpub, (char *) &msg, sizeof(msg));
        if ((fdpriv = open(msg.privfifo, O_RDONLY)) == -1) {
            perror(msg.privfifo);
            exit(3);
        }
        int n;
        while ((n = read(fdpriv, currentline, LEN)) > 0) {
            for (char * i = currentline; *i != '\0'; i++){
                if ((*i >= 48) && (*i <= 57)){
                    if (last){	//d-d
                        sum = sum + *i - 48;
                    } else {	//c-d
                        sum = *i - 48;
                        last = 1;
                    }
                } else {	//d-c
                    if (last){
                        printf("%d", sum);
                        last = 0;
                        printf("%c", *i);
                    } else {	//c-c
                        printf("%c", *i);
                    }
                }
            }
        }
        close(fdpriv);
    }
    unlink(msg.privfifo);
    return 0;
}