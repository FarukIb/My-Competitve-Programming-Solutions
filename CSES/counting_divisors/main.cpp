#include <bits/stdc++.h>
#define mp make_pair

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

void make_multipl() {

    vector<int> sito(maxn, 1);
    /*for (int i = 2; i < maxn; i++) {
        if (sito[i] != 1)
            continue;
        for (int j = i; j < maxn; j++) {
            int stepen = 0;
            int fake = j;
            while (fake % i == 0)
                stepen++, fake /= i;
            sito[i] *= stepen + 1;
        }
    }*/
    for (int i = 1; i < maxn; i++)
        for (int j = i; j < maxn; j++)
            sito[j]++;
}


const int maxn = 1e6 + 10;
vector<int> salaka_sito;
void make_sito() {
    salaka_sito.resize(maxn, 1);
    for (int i = 2; i < maxn; i++) {
        if (salaka_sito[i] != 1)
            continue;
        for (int j = i; j < maxn; j += i) {
            if (salaka_sito[j] == 1)
                salaka_sito[j] = i;
        }
    }
}

void get_factors(int curr, vector<int> &facts) {
    if (curr == 1)
        return;
    facts.push_back(salaka_sito[curr]);
    get_factors(curr / salaka_sito[curr], facts);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    make_sito();
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector<int> facts;
        get_factors(n, facts);

        map<int, int> guys;
        for (int i : facts) {
            guys[i]++;
        }

        int out = 1;
        for (pii s : guys)
            out *= s.second + 1;
        cout << out << "\n";
    }
}