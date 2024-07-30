#include <bits/stdc++.h>
using namespace std;


int main() {
    // A
    int niz[10];
    for (int i = 0; i < 10; i++)
        cin >> niz[i];

    bool prvi = true;
    for (int i = 0; i < 10; i++) {
        if (niz[i] % 2 == 0)
        {
            if (prvi)
                prvi = false;
            else
                cout << ", ";
             cout << niz[i];
        }
    }
    cout << ".\n";

    //B
    for (int i = 0; i < 10; i++) {
        if (i % 2 == 1)
            niz[i] *= 2;
    }
    for (int i = 0; i < 10; i++)    
        cout << niz[i] << " ";
    cout << "\n";

    //C
    double niz2[10] = {1.3, 43.12, 4.31, 54.12, -134.3, -31.43, 314.13, 55.3, -87.123, 981.2};
    for (int i = 0; i < 10; i++)
        niz2[i] += (double)niz[i];
}