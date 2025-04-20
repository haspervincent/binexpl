#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> // voor rea
#include <string.h>

typedef struct {
    char *name;
    void (*func)(char *);
} user_s;

void secret(char *ignored)
{
    printf("FLAG: YOU GOT IN!\n");
    fflush(stdout); // Zorg dat het geprint wordt
}

void greet(char *name) 
{
    printf("Hello, %s\n", name);
}

void menu() {
    puts("[1] Create user");
    puts("[2] Delete user");
    puts("[3] Set name");
    puts("[4] Call function");
    puts("[5] Exit");
    printf("> ");
}

user_s *user = NULL;

void create(void) 
{
    user = malloc(sizeof(user_s));
    user->func = greet;
    user->name = NULL;
    puts("User created.");
}

void del() {
    free(user);
    puts("User deleted.");
    // Let op: user pointer blijft staan (UAF)
}

void setname() {
    if (!user) {
        puts("No user!");
        return;
    }

    printf("Enter your name: ");
    read(0, user, sizeof(user_s));  // ⚠ Overschrijft de freed user direct
    puts("Name set.");
}

void call() {
    if (user) {
        user->func(user->name);  // Roep function pointer aan
    } else {
        puts("No user!");
    }
}

int main() {
    setbuf(stdout, NULL);

    int choice;
    while (1) {
        menu();
        scanf("%d", &choice);
        getchar(); // flush newline

        switch (choice) 
        {
            case 1: create(); break;
            case 2: del(); break;
            case 3: setname(); break;
            case 4: call(); break;
            case 5: exit(0); break;
            default: puts("Invalid choice."); break;
        }
    }
}
