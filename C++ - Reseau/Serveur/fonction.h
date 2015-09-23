#ifndef FONCTION
#define FONCTION

typedef struct M
{
    char option;
    char ctrl;
    short int taille;
    char data[512];
} Message;

            struct put
            {
                int     sock;
                char    data[512];
            };

void *mainThreadDown(void*);
void *mainThreadUp(void*);
void *mainPut(void*);
void *mainGet(void*);

#endif

