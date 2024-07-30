#include <bits/stdc++.h>
#define mp make_pair

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

const int maxn = 1e6 + 10;
vector<vector<int> > precalc;
void make_sito() {
    precalc.resize(11, vector<int>(maxn, 0));

    vector<int> num(maxn, 0);
    for (int i = 2; i < maxn; i++) {
        if (num[i] != 0)
            continue;
        num[i] = 1;
        for (int j = 2 * i; j < maxn; j += i)
            num[j]++;
    }

    for (int i = 0; i <= 10; i++)
    {
        for (int j = 1; j <= maxn; j++)
        {
            if (num[j] == i)
                precalc[i][j]++;
            precalc[i][j] += precalc[i][j - 1];
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    make_sito();
    int t;
    cin >> t;
    while (t--) {
        int a, b, n;
        cin >> a >> b >> n;
        cout << precalc[n][b] - precalc[n][a - 1] << "\n";
    }
}