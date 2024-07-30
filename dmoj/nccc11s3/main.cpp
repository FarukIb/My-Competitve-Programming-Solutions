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

    int n, k;
    cin >> n >> k;
    vector<vector<ll> > dp(n, vector<ll>(n));
    dp[0][0] = 1;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= i; j++) {
            if (i == j and !(i == n - 1 and j == n - 1))
                continue;
            for (int k1 = 0; i - k1 >= 0 and k1 <= k; k1++)
                for (int k2 = 0; j - k2 >= 0 and k2 <= k; k2++)
                    if (i - k1 < j || (i - k1 == j and j == 0))
                        dp[i][j] += dp[i - k1][j - k2], dp[i][j] %= mod;
        }
    }

    cout << dp[n - 1][n - 1] << "\n";
}