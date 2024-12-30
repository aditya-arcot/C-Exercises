// pseudo-random number generator with seed

#include <stdio.h>

int rand(void);
void srand(unsigned int seed);

static unsigned long next = 1;

int main(void)
{
    srand(2);
    printf("%d\n", rand());
    printf("%d\n", rand());
    printf("%d\n", rand());
}

int rand(void)
{
    next = next * 1103515245 + 12345;
    return (unsigned int)(next / 65536) % 32768;
}

void srand(unsigned int seed)
{
    next = seed;
}
