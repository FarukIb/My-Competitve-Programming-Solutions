#include <bits/stdc++.h>
#define mp make_pair
#define all(a) a.begin(), a.end()

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    srand(time(0));

    int n = 8;
    vector<int> perm(n);
    for (int i = 0; i < n; i++)
        perm[i] = i + 1;
    do {
        fstream fin("inp.txt");
        fin << 1<< endl;
        fin << n << endl;
        for (int i = 0; i < n; i++)
            fin << perm[i] << " ";
        fin << endl;
        system("./main < inp.txt > string.txt");
        fstream fina("final.txt");
        fina << 2 << endl;
        fina << n << endl;
        int a = rand() % n, b = rand() % n;
        while (a == b)
            a = rand() % n, b = rand() % n;
        swap(perm[a], perm[b]);
        fstream str("string.txt");
        string g;
        str >> g;
        for (int i = 0; i < n; i++)
            fina << perm[i] << " ";
        fina << endl;
        fina << g << endl;

        system("./main < final.txt > out.txt");
        fstream out("out.txt");
        bool print = false;
        swap(perm[a], perm[b]);
        for (int i = 0; i < n; i++) {
            int c;
            out >> c;
            if (c != perm[i]) {
                print = true;
            }
        }
        if (print) {
            cout << a <<" " << b << ": ";
            for (int i = 0; i < n; i++)
                cout << perm[i] << " ";
            cout << endl;
            break;
        }
    } while (next_permutation(all(perm)));
}