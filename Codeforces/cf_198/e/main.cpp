#include <bits/stdc++.h>
#define mp make_pair

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

const int maxn = 2e3 + 10;
const ll mod = 1e9 + 7;

ll fact[maxn];
ll memo[maxn][maxn];
ll dp(ll n, ll k) {
    if (k == 1) 
        return n * fact[n] % mod;
    if (k == 0)
        return fact[n];
    if (memo[n][k] != -1)
        return memo[n][k];
    return memo[n][k] = ((dp(n, k - 1) * n) % mod + (dp(n + 1, k - 2) * (k - 1LL)) % mod) % mod;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    fact[0] = 1;
    for (ll i = 1; i < maxn; i++)
        fact[i] = (fact[i - 1] * i) % mod;
    int n;
    cin >> n;
    vector<int> perm(n);
    set<int> not_placed; for (int i = 1; i <= n; i++) not_placed.insert(i);
    for (int i = 0; i < n; i++)
    {
        cin >> perm[i];
        not_placed.erase(perm[i]);
    }
    int k = 0;
    for (int s : not_placed)
        if (perm[s - 1] == -1)
            k++;
    for (int i = 0; i < maxn; i++)
        for (int j = 0; j < maxn; j++)
            memo[i][j] = -1;
    cout << dp(not_placed.size() - k, k) << "\n";
}