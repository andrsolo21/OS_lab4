#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include "server.h"
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv) {
    int fdpub, fdpriv;
    struct message msg;

    char chr;
    int last = 0;

    while (1) {
        if ((fdpub = open(PUBLIC_CHAN, O_RDONLY)) == -1) {
            perror(PUBLIC_CHAN);
            exit(1);
        }
        while (read(fdpub, (char *) &msg, sizeof(msg)) > 0) {
            if ((fdpriv = open(msg.privfifo, O_WRONLY)) == -1) {
                perror(msg.privfifo);
                break;
            }

            char result[LEN];
            size_t  result_i = 0;
            for (size_t i = 0; i< strlen(msg.string); i++) {
                chr = msg.string[i];
                if ((chr >= 48) && (chr <= 57)){
                    if (last){
                        result[result_i++] = chr;
                    } else {
                        result[result_i++] = '(';
                        result[result_i++] = chr;
                        last = 1;
                    }
                } else {
                    if (last){
                        result[result_i++] = ')';
                        result[result_i++] = chr;
                        last = 0;
                    } else {
                        result[result_i++] = chr;
                    }
                }
            }
            result[result_i++] = 0;
            write(fdpriv, result, result_i);

            close(fdpriv);
        }
        close(fdpub);
    }
    return 0;
}