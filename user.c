#include <stdio.h>
#include <stdlib.h>

#define FLAG_SIZE 256


typedef struct {
    char *name;
    void (*func)(char *);
} user_s;


void clear(void)
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}


void secret(void)
{
    FILE *file = fopen("flag.txt", "r");
    if (!file) {
        printf("failed to open flag.txt\n");
        return;
    }

    char flag[FLAG_SIZE];
    if (fgets(flag, sizeof(flag), file)) {
        printf("%s\n", flag);
    } else {
        printf("failed to read the flag\n");
    }

    fclose(file);
}


void greet(char *name) 
{
    printf("hello %s\n", name);
}


user_s *user = NULL;


void create(void)
{
    user = malloc(sizeof(user_s));
    user->name = NULL;
    user->func = greet;
    printf("user created\n");
}


void del(void)
{
    free(user);
    printf("user deleted\n");
}


void setname(void)
{
    if (!user) {
        printf("no user\n");
        return;
    }

    printf("enter your name: ");
    fread(user, sizeof(user_s), 1, stdin);
    printf("name set\n");
}


void call(void)
{
    if (user) {
        user->func(user->name);
    } else {
        printf("no user\n");
    }
}


int main(void)
{
    setbuf(stdout, NULL);
    
    char choice;
    
    clear();

    printf("                                ,,,                                         \n");
    printf("                               (o o)                                        \n");
    printf("                       ----oOO--( )--OOo----                                \n");
    printf("                                                                            \n");
    printf("[1. create user] [2. delete user] [3. set name] [4. call function] [5. exit]\n");
    
    while (1) {
        printf("\nchoice> ");

        choice = getchar(); 

        while (getchar() != '\n');    
        
        switch (choice) {
            case '1':
                create();
                break;
            case '2':
                del();
                break;
            case '3':
                setname();
                break;
            case '4':
                call();
                break;
            case '5':
                exit(EXIT_SUCCESS);
                break;
            default:
                printf("invalid choice\n");
                break;
        }
    }

    return 0;
}
