#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#define        R  0        /*  stdin                      */
#define        W  1   		/*stdout 					  */ 

int main(void) {
    int fd[2]; // 0 - Read, 1 - Write
    int status;
    switch (fork()) {
        case -1: {
            perror("Ошибка при вызове fork() \n");
            exit(1);
        }
        case 0: {
            pipe(fd);
            switch (fork()) {
                case -1: {
                    perror("Ошибка при вызове fork() \n");
                    exit(2);
                }
                case 0: {
                    close(fd[W]); // Close write
                    dup2(fd[R], 0);
                    execl("output/f1", "output/f1", NULL);
                    perror("Ошибка при вызове 'output/f1'\n");
                    exit(3);
                }
                default: {
                    close(fd[R]); // Close read
                    dup2(fd[W], 1);
                    execl("output/f2", "output/f2", NULL);
                    perror("Ошибка при вызове 'output/f2'\n");
                    exit(4);
                }
            }
        }
        default: {
            wait(&status);
            exit(1);
        }
    }
}