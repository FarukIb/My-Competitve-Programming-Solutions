#include <stdio.h>

void main() {
    int n;
    scanf("%d", &n);

    int cpy = n;
    int paran = 1; /* ako je paran ova varijabla je 1 inace 0 */
    do {
        if (paran)
            paran = 0;
        else
            paran = 1;
        cpy--;
    } while (cpy > 0);

    int dobro = 1; /* ako je dobro 0 izlaz je ne */
    if (paran == 1 && n > 0 && n <= 100) {
        printf("NE\n");
        return;
    }

    int mat[100][100], i, j;
    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
            scanf("%d", &mat[i][j]);
    
    int val = mat[0][0], prsten = 0;
    for (prsten = 0; prsten <= n / 2; prsten++) {
        i = prsten, j = prsten;
        /* kretnja desno */
        for (; i < n - prsten - 1; i++)
            if (mat[i][j] != val)
                dobro = 0;
        
        /* kretanje dole */
        for (; j < n - prsten - 1; j++)
            if (mat[i][j] != val)
                dobro = 0;

        /* kretanje lijevo */
        for (; i > prsten; i--)
            if (mat[i][j] != val)
                dobro = 0;

        /* kretanje gore */
        for (; j > prsten; j--)
            if (mat[i][j] != val)
                dobro = 0;
        
        val++;
    }

    if (dobro == 1)
        printf("DA\n");
    else
        printf("NE\n");
}