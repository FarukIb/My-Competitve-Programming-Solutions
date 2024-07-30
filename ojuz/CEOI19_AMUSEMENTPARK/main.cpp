#include <bits/stdc++.h>
#define mp make_pair
#define all(a) a.begin(), a.end()

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

const ll mod = 998244353;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int n, m;
    cin >> n >> m;
    vector<vector<pii> >adj(n+1);
    for (int i = 0; i < m; i++) {
        int f, t;
        cin >> f >> t;
        f--, t--;
        adj[f].push_back({t, 0});
        adj[t].push_back({f, 1});
    }
    vector<ll> dp(1 <<n);
    vector<ll> numways(1 << n);
    dp[0] = 0;
    numways[0] = 1;
    vector<vector<int> > masks(n+1);
    for (int i = 0; i < 1 << n; i++)
        masks[__builtin_popcount(i)].push_back(i);
    masks.pop_back();
    for (vector<int> a : masks) {
        for (int mask : a) {
            for (int to_add = 0; to_add < n; to_add++) {
                ll c = 0;
                if (((1 << to_add) & mask) != 0)
                    continue;
                for (pii b : adj[to_add]) {
                    if (((1 << b.first) & mask) == 0)
                        continue;
                    c += b.second;
                }
                int new_mas = (1 << to_add) + mask;
                numways[new_mas] += numways[mask]; numways[new_mas] %= mod;
                dp[new_mas] += (dp[mask] + (numways[mask] * c) % mod) % mod;
                dp[new_mas] %= mod;
            }
        }
    }
    cout << dp[(1 << n) - 1] << "\n";
}