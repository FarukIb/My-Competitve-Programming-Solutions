#include <bits/stdc++.h>
#define ll long long

using namespace std;

ll bin[10001][5];
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    bin[0][0] = 1;
    for (int i = 1; i <= 10000; i++) {
        bin[i][0] = 1;
        for (int j = 1; j <= 4; j++)
            bin[i][j] = bin[i - 1][j] + bin[i - 1][j - 1];
    }

    ll n;
    while (cin >> n) {
        map<int, int> hist; int maxi = 0;
        for (int i = 0; i < n; i++)
        {
            int x;
            cin >> x;
            maxi = max(x, maxi);
            hist[x]++;        
        }

        map<int, ll> cnt;
        ll out = 0;
        for (int GCD = maxi; GCD > 1; GCD--) {
            int numDiv = 0;
            for (int j = GCD; j <= maxi; j += GCD)
                numDiv += hist[j];
            cnt[GCD] += bin[numDiv][4];
            out += cnt[GCD];

            for (int j = 2; j * j <= GCD; j++) {
                if (GCD % j != 0)
                    continue;
                cnt[j] -= cnt[GCD];
                if (j * j != GCD)
                    cnt[GCD / j] -= cnt[GCD];
            }
        }

        cout << bin[n][4] - out << "\n";
    }
}