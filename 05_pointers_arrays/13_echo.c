// echo command-line args

#include <stdio.h>

int main(int argc, char *argv[]) {
    // int i;
    // for (i = 1; i < argc; i++)
    //     printf("%s%s", argv[i], (i < argc - 1) ? " " : "");

    while (--argc > 0)
        printf((argc > 1) ? "%s " : "%s", *++argv);

    printf("\n");
}
