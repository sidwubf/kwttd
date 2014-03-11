#include "kwttd_util.h"
#include <stdio.h>
#include <stdlib.h>

int
main(int argc, char *argv[]) {
    int limit = 10;
    char *a, *b, *c, *d;
    a = "aaaaa";
    b = "bbbbbb";
    c = "ccccc";
    d = "aaaaa";

    printf("%d\n", kwttd_strcmp(a, b));
    printf("%d\n", kwttd_strcmp(a, c));
    printf("%d\n", kwttd_strcmp(a, d));

    char *e;
    e = "abcdertyuiop";
    printf("%s\n", kwttd_strsub(e, 1, 5));
    exit(0);
}
