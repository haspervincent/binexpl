#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *name;
    void (*fp)(void);
} user_s;

user_s *u = NULL;

void clear(void) {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void greet(void) {
    if (u && u->name) {
        printf("hello %s\n", u->name);
    }
}

void secret(void) {
    printf("flag{aodoisaudoiadoiado}\n");
}

void alloc_user(void) {
    if (!u) {
        u = malloc(sizeof(user_s));
        u->name = malloc(64);
        u->fp = greet;
        printf("allocated memory for user\n");
    } else {
        printf("user already exists\n");
    }
}

void free_user(void) {
    if (u) {
        free(u->name);
        free(u);
        // u = NULL;
        printf("freed memory for user\n");
    } else {
        printf("no user to free\n");
    }
}

void set_name(void) {
    if (u) {
        printf("enter name: ");
        fgets(u->name, 64, stdin);
        size_t len = strlen(u->name);
        if (len > 0 && u->name[len - 1] == '\n')
            u->name[len - 1] = '\0';
        printf("user name updated\n");
    } else {
        printf("no user to set name for\n");
    }
}

void call_user_func(void) {
    if (u) {
        printf("calling user function...\n");
        u->fp();
    } else {
        printf("no user function to call\n");
    }
}

int main(void) {
    setbuf(stdout, NULL);
    clear();
    char c;
    printf("                                    ,,,                                    \n");
    printf("                                   (o o)                                   \n");
    printf("                           ----oOO--( )--OOo----                           \n");
    printf("                                                                           \n");
    printf("[1] allocate user  [2] free user  [3] set name  [4] call function  [5] exit\n");
    for (;;) {
        printf(">>> ");
        c = getchar();
        while (getchar() != '\n');
        switch (c) {
        case '1':
            alloc_user();
            break;
        case '2':
            free_user();
            break;
        case '3':
            set_name();
            break;
        case '4':
            call_user_func();
            break;
        case '5':
            printf("exiting...\n");
            exit(0);
        default:
            printf("invalid option\n");
            break;
        }
    }
    return 0;
}
