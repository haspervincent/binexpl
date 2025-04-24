#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
#define CLEAR_CMD "cls"
#else
#define CLEAR_CMD "clear"
#endif

#define NAME_SIZE 32
#define NOTE_SIZE 32

typedef struct {
    char *name;
    void (*fp)(char *);
} user_s;

void clrscr(char *cmd)
{
    system(cmd);
}

void prtflg(void)
{
    printf("flag{aiojsoajso}\n");
}

void grtusr(char *name)
{
    printf("hello %s\n", name);
}

user_s* alcusr(void)
{
    user_s *user = malloc(sizeof(user_s));
    user->name = malloc(NAME_SIZE);
    user->fp = grtusr;
    return user;
}

void frusr(user_s *user)
{
    free(user->name);
    free(user);
}

void calusr(user_s *user)
{
    user->fp(user->name);
}

int main(void)
{
    setbuf(stdout, NULL);

    clrscr(CLEAR_CMD);

    printf("                                    ,,,                                    \n");
    printf("                                   (o o)                                   \n");
    printf("                           ----oOO--( )--OOo----                           \n");
    printf("                                                                           \n");
    printf("[1] create user  [2] delete user  [3] greet user  [4] create note  [5] exit\n");
    
    user_s *user = NULL;
    char *note = NULL;
    char choice;
    
    for (;;) {
        printf(">>> ");
        choice = getchar(); while (getchar() != '\n');
        switch (choice) {
        case '1':
            user = alcusr();
            printf("enter name: ");
            fgets(user->name, NAME_SIZE, stdin);
            user->name[strcspn(user->name, "\n")] = '\0';
            break;
        case '2':
            frusr(user);
            break;
        case '3':
            grtusr(user->name);
            break;
        case '4':
            note = malloc(NOTE_SIZE);
            printf("enter note: ");
            fgets(note, NOTE_SIZE, stdin);
            note[strcspn(note, "\n")] = '\0';
            break;
        case '5':
            exit(0);
            break;

        default:
            printf("invalid option\n");
            break;
        }
    }
    
    return 0;
}
