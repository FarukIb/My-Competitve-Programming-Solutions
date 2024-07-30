#include <bits/stdc++.h>
#define all(a) a.begin(), a.end()
#define mp make_pair

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

const ll mod = 1e9 + 7;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int n, m;
    cin >> n >> m;
    vector<ll> dp((1 << m));
    vector<ll> val(n + 1, 1);
    for (int i = 0; i < n; i++) {
        val[i + 1] = val[i] * 2 % mod;
        int o;
        cin >> o;
        ll mask = 0;
        for (int j = 0; j < o; j++) {
            int po;
            cin >> po;
            mask += (1 << (po - 1));
        }
        dp[mask]++;
    }

    for (int mask = 0; mask < (1 << m); mask++)
        dp[mask] = val[dp[mask]] - 1;

    for (int bit = 0; bit < m; bit++)
        for (int mask = 0; mask < (1 << m); mask++)
            if ((1 << bit) & mask)
                dp[mask] = (dp[mask] + dp[mask - (1 << bit)] + (dp[mask]*dp[mask - (1 << bit)]) % mod) % mod;
    ll out = 0; 
    for (int mask = 0; mask < (1 << m); mask++)
    {
        int popc = __builtin_popcount(mask);
        if ((popc + m) % 2)
            out = (out - dp[mask] + mod) % mod;
        else
            out = (out + dp[mask]) % mod;
    }
    cout << out << "\n";
}