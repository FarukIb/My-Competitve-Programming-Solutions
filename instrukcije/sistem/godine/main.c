#include <stdio.h>
#include <ctype.h>
#include <string.h>
#define GODINA 2020

void main() {
    int godiste;
    printf("Unesite godinu rodjenja: ", &godiste);
    scanf("%d", &godiste);


    /* UNOS GODINA*/
    int godine = GODINA - godiste;
    if (godine < 0) {
        printf("Neispravna godina rodjenja!\n");
        return;
    }

   /* UNOS SPOLA */
    char spol_char;
    printf("Unesite spol osobe (m/M ili z/Z): ");
    scanf(" %c", &spol_char);
    spol_char = tolower(spol_char);

    char spol[10];
    if (spol_char == 'm')
        strcpy(spol, "musko");
    else if (spol_char == 'z')
        strcpy(spol, "zensko");
    else {
        printf("Pogresan unos spola osobe!\n");
        return; 
    }

    char kategorija[20];
    /* PROCESUIRANJE GODINA */
    if (godine < 6)
        stpcpy(kategorija, "prije skola");
    else if (godine < 14)
        strcpy(kategorija, "osnovna skola");
    else if (godine < 18)
        strcpy(kategorija ,"srednja skola");
    else if (godine <= 23)
        strcpy(kategorija ,"fakultet");
    else
        strcpy(kategorija ,"ostalo");

    printf("Osoba ima %d godina/e/u, klasificirana je u kategoriju: '%s', %s je.\n", godine, kategorija, spol);
}

/*


*/