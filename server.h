#ifndef SERVER
#define SERVER
#define LEN  255
struct message {
    char privfifo[15];
    char string[LEN];
};
#define PUBLIC_CHAN "public"

#endif