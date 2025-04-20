#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NOTE_SIZE 256
#define FLAG_SIZE 256

#ifdef _WIN32
    #define CLEAR_CMD "cls"
#elif __linux__ || __APPLE__
    #define CLEAR_CMD "clear"
#else
    #define CLEAR_CMD NULL
#endif

void clear_terminal(void) 
{
    if (CLEAR_CMD != NULL) {
        system(CLEAR_CMD);
    }
}

typedef struct {
    char *text;
    void (*show)(void);
} note_t;

note_t *note = NULL;

void print_flag(void) 
{
    FILE *file = fopen("flag.txt", "r");
    if (!file) {
        printf("failed to open flag.txt\n");
        return;
    }

    char flag[FLAG_SIZE];
    if (fgets(flag, sizeof(flag), file)) {
        printf("[+] %s\n", flag);
    } else {
        printf("failed to read the flag\n");
    }

    fclose(file);
}

void show_note(void) 
{
    if (note && note->text) {
        printf("note: %s\n", note->text);
    } else {
        printf("no note found\n");
    }
}

void create_note(void) 
{
    if (note) {
        printf("note already exists\n");
        return;
    }

    note = malloc(sizeof(note_t));
    if (!note) {
        printf("allocation failed\n");
        return;
    }

    note->text = malloc(NOTE_SIZE);
    if (!note->text) {
        free(note);
        printf("allocation failed\n");
        return;
    }

    note->show = show_note;

    printf("enter your note: ");
    if (fgets(note->text, NOTE_SIZE, stdin)) 
    {
        note->text[strcspn(note->text, "\n")] = 0;  // remove newline character from fgets
        printf("note created\n");
    } else {
        printf("input error\n");
    }
}

void delete_note(void) 
{
    if (!note) {
        printf("no note to delete\n");
        return;
    }

    free(note->text);
    free(note);
    // note = NULL;
    printf("note deleted\n");
}

void execute_note(void) 
{
    if (note) {
        note->show();
    } else {
        printf("no note exists\n");
    }
}

void run(void) 
{
    char choice;

    while (1) {
        printf("choice: ");
        choice = getchar();
        while (getchar() != '\n'); 

        switch (choice) {
            case '1':
                create_note();
                break;
            case '2':
                delete_note();
                break;
            case '3':
                execute_note();
                break;
            case '4':
                printf("exiting program\n");
                exit(EXIT_SUCCESS);
            default:
                printf("invalid option\n");
        }
    }
}

int main(void) 
{
    clear_terminal();

    printf("=== noteio ===\n");
    printf("[1. create note] [2. delete note] [3. show note] [4. exit]\n");

    run();
    return 0;
}
