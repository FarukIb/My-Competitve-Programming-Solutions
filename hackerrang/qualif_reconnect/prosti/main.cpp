#include <bits/stdc++.h>
#define mp make_pair

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

bool sito[(int)2e6];

void makesito() {
    sito[1] = true;
    for (int i = 2; i * i <= 1e6; i++) {
        if (sito[i])
            continue;
        for (int j = i * i; j <= 1e6; j += i)
            sito[j] = true;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    makesito();
    int x, y;
    cin >>x >> y;
    int out = 0;
    for (int i = x; i <= y; i++)
        if (!sito[i])
            out++;
    cout << out << "\n";
}