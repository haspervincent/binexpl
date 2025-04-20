#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *data;
    void (*fp)(void);
} chunk_s;

void print_flag(void) 
{
    FILE *file = fopen("flag.txt", "r");
    if (file == NULL) {
        printf("[ERROR] - failed to open 'flag.txt'\n");
        return;
    }
    char flag[256];
    if (fgets(flag, sizeof(flag), file) != NULL) {
        printf("[+] %s\n", flag);
    } else {
        printf("[ERROR] - failed to read the flag\n");
    }
    fclose(file);
}

void do_nothing(void)
{
    printf("i'm doing nothing\n");
}

int main(void)
{
    printf("[INFO] - Step 1: allocating real_chunk...\n");
    chunk_s *real_chunk = malloc(sizeof(chunk_s));
    printf("[INFO] - real_chunk struct allocated at: %p\n", (void *)real_chunk);

    real_chunk->data = malloc(64);
    printf("[INFO] - real_chunk->data allocated at: %p\n", (void *)real_chunk->data);

    real_chunk->fp = do_nothing;
    printf("[INFO] - real_chunk->fp is set to do_nothing() at: %p\n", (void *)do_nothing);
    printf("[INFO] - print_flag is located at: %p\n", (void *)print_flag);

    printf("[INFO] - Step 2: freeing real_chunk...\n");
    free(real_chunk);
    printf("[INFO] - real_chunk has been freed, but pointer still exists (dangling)\n");

    printf("[INFO] - Step 3: attacker allocates fake chunk (same size)...\n");
    void *attacker_buffer = malloc(sizeof(chunk_s));
    printf("[INFO] - attacker_buffer allocated at: %p\n", (void *)attacker_buffer);

    chunk_s *fake_chunk = attacker_buffer;
    fake_chunk->data = NULL;
    fake_chunk->fp = print_flag;
    printf("[INFO] - attacker overwrites fp with print_flag at: %p\n", (void *)print_flag);

    printf("[INFO] - Step 4: calling real_chunk->fp()...\n");
    real_chunk->fp(); // Should now call print_flag()

    printf("[INFO] - Exploit attempt complete.\n");

    return EXIT_SUCCESS;
}
