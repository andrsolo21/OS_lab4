#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#define R 0
#define W 1

int main(void) {
    int p[2], q[2];
    FILE *fp;
    pipe(p);
    pipe(q);
    switch (fork()) {
        case -1: {
            perror("Ошибка при вызове fork() \n");
            exit(1);
        }
        case 0: {
            close(p[W]);
            if (dup2(p[R], R) == -1) {
                perror("Error with pipe 'p' in 'output/f1' for read");
            }
            close(p[R]);
            close(q[R]);
            if (dup2(q[W], W) == -1) {
                perror("Error with pipe 'q' in 'output/f1' for write");
            }
            close(q[W]);
            execl("output/f1", "output/f1", NULL);
            perror("output/f1: call error");
            exit(1);
        }
        default: {
            close(p[R]);
            close(q[W]);

            fp = fdopen(p[W], "w");
            const size_t LEN = 51;
            char string[LEN];

            int chr;
            const size_t MAX_COUNT = 8;
            size_t count = 0;
			
			
            while (fgets(string, LEN, stdin) != NULL) {
                fprintf(fp, "%s", string);
            }
            fclose(fp);
			
			
            fp = fdopen(q[R], "r");

            char currentline[LEN];
            int sum = 0;
            int last = 0;
            int temp = 0;
            while (fgets(currentline, LEN, fp) != NULL) {

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
			
            fclose(fp);
            exit(0);
        }
    }
}