// print input character count

#include <stdio.h>

int main()
{
    int count;

    // count = 0;
    // while (getchar() != EOF)
    //     ++count;

    for (count = 0; getchar() != EOF; ++count)
        ;
    printf("%d characters\n", count);
}