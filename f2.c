#include <stdio.h>
#include <string.h>

int main() {
    const size_t LEN = 51;
    char currentline[LEN];
	int sum = 0;
	int last = 0;
    while (fgets(currentline, LEN, stdin) != NULL) {
		
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
    printf("\n");
    return 0;
}