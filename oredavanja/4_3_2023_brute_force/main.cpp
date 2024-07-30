#include <bits/stdc++.h>
#define mp make_pair

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

int suma_svih(vector<int> &perm) {
    int summ = 0;
    for (int s : perm)
        summ += s;
    return summ;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int n;
    cin >> n;
    vector<int> perm(n);
    for (int i = 0; i <n; i++)
        perm[i] = i + 1;

    int suma = 0, broj_permutacija = 0;
    do {
        suma += suma_svih(perm);
        broj_permutacija++;
    } while (next_permutation(perm.begin(), perm.end()));

    cout << suma / broj_permutacija << "\n";
}