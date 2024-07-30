#include <stdio.h>

int izbaci_najcesci(char *str) {
    int broj_poj[1001];
    for (int i = 0; i < 1001; i++)
        broj_poj[i] = 0;
    
    int broj = 0, len = 0;
    while (*str != '\0') {
        if (*str >= '0' && *str <= '9')
            broj *= 10, broj += *str - '0', len++;
        else if (len != 0)
            broj_poj[broj]++, broj = 0, len = 0;
        str++;
    }

    // u slučaju da je zadnje slovo broj, taj broj neće biti procesuiran
    if (len != 0)
        broj_poj[broj]++;


    // 
    int najveci = 0;
    for (int i = 0; i <= 1000; i++) {
        if (broj_poj[i] > broj_poj[najveci])
            najveci = i;
    }

    return najveci;
}

void main() {
    char *str;
    scanf("%s", &str);
    printf("%d\n", izbaci_najcesci(str));
}