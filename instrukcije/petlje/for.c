#include <stdio.h>

int main() {
    int i;
    for (i = 0; i <= 5; i++) {
        printf("%d\n", i);
    }

    
    puts(""); // ekvilaventno scanf("\n");
    for (i = 10; i >= 0; i -= 2) {
        printf("%d\n", i);
    }
    puts(""); // ekvilaventno scanf("\n");
    for (i = 1; i <= 100; i *= 2) {
        printf("%d\n", i);
    }
}