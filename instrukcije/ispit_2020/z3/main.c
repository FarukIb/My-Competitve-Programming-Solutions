#include <stdio.h>
#include <math.h>

struct Student {
    char ime[20], prezime[20];
    int ocjene[1000];
    int br_ocjena;
};

void prosjeci(struct Student* niz) {
    struct Student* novi;
}

float zaokruzi(float x) {
    x *= 100;
    int s = roundf(x);
    x = s;

    x /= 100;
    return x;
}

void main() {
    float x;
    scanf("%f", &x);

    printf("%f\n", zaokruzi(x));
}