#include <stdio.h>
#include <string.h>
//123?125 40?41 91?93
int main() {
    int chr;
	int last = 0;
    while ((chr = fgetc(stdin)) != EOF) {
		if ((chr >= 48) && (chr <= 57)){
			if (last){
				printf("%c", chr);
			} else {
				printf("%c", 40);
				printf("%c", chr);
				last = 1;
			}
		} else {
			if (last){
				printf("%c", 41);
				printf("%c", chr);				
				last = 0;
			} else {
				printf("%c", chr);
			}
		}
    }
    return 0;
}