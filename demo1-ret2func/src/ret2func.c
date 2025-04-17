// demo1 > src > ret2func.c
/*
 * simple buffer overflow vulnerability that allows overwriting the return address.
 */
#include <stdio.h>

void print_flag(void)
{
    FILE *file = fopen("flag.txt", "r");
    if (file == NULL) {
        printf("[ERROR] - failed to open 'flag.txt'\n");
        return;
    }
    char flag[256];
    if (fgets(flag, sizeof(flag), file) != NULL) {
        printf("%s\n", flag);
    } else {
        printf("[ERROR] - failed to read the content of 'flag.txt'\n");
    }
    fclose(file);
}

void random_function(void)
{
    char x[28];
    printf(">>> ");
    scanf("%s", x);
    printf("[INFO] - u filled in: %s\n", x);
}

int main(void)
{
    random_function();
    return 0; 
}