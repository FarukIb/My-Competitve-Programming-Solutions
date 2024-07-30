#include <bits/stdc++.h>
#define mp make_pair
#define all(a) a.begin(), a.end()

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

const ll mod = 1e9 + 7;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    freopen("spainting.in", "r", stdin);
    freopen("spainting.out", "w", stdout);

    ll n, m, k;
    cin >> n >> m >> k;
    vector<ll> dp(n+1); dp[0] = 0;
    ll ans = 1;
    for (int i = 1; i <= n; i++) {
        if (i < k)
        {
            dp[i] = dp[i - 1] * m + m; dp[i] %= mod;
        }
        else
        {
            dp[i] = (m*dp[i - 1]) % mod;
            dp[i] -= (m - 1)*dp[i - k] % mod;
            dp[i] %= mod;
        }
        ans *= m;
        ans %= mod;
    }

    ans -= (dp[n] - dp[n - 1]) % mod;
    ans %= mod;
    if (ans < 0)
        ans += mod;
    cout << ans << "\n";
}