#include <stdio.h>
#include <stdlib.h>

#ifdef _WIN32
#define CLEAR_CMD "cls"
#else
#define CLEAR_CMD "clear"
#endif

#define NAME_BUF 16
#define NOTE_BUF 32

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
    if (!user) return NULL;
    user->name = malloc(NAME_BUF);
    if (!user->name) {
        free(user);
        return NULL;
    }
    user->fp = grtusr;
    return user;
}

void frusr(user_s *user)
{
    if (user) {
        free(user->name);
        free(user);
    }
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
            if (user) {
                printf("user already exists\n");
            } else {
                user = alcusr();
                if (user) {
                    printf("enter name: ");
                    fgets(user->name, NAME_BUF, stdin);
                    printf("user created\n");
                } else {
                    printf("failed to create user\n");
                }
            }
            break;

        case '2':
            if (user) {
                frusr(user);
                printf("user deleted\n");
            } else {
                printf("no user to delete\n");
            }
            break;

        case '3':
            if (user) {
                calusr(user);
            } else {
                printf("no user to greet\n");
            }
            break;

        case '4':
            if (note) {
                free(note);
            }
            note = malloc(NOTE_BUF);
            if (note) {
                printf("enter note: ");
                fgets(note, NOTE_BUF, stdin);
                printf("note created\n");
            } else {
                printf("failed to create note\n");
            }
            break;

        case '5':
            printf("exiting\n");
            exit(0);

        default:
            printf("invalid option\n");
            break;
        }
    }

    return 0;
}
