#include <stdio.h>
#include <stdlib.h>

void main() {
    FILE *file = fopen("input.txt", "r");

    char *x = calloc(100, sizeof(char));
    char *y = calloc(100, sizeof(char));

    //fgets(x, 100, file);
    //fgets(y, 100, file);

    fscanf(file, "%s", x);
    fscanf(file, "%s", y);

    printf("%s\n%s\n", x, y);
}