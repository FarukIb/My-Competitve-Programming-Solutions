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

    int n, m;
    cin >> m >> n;
    vector<vector<vector<ll> > > dp(n+1, vector<vector<ll> >(m+1, vector<ll>((1<<(m+2)))));
    dp[0][m][0] = 1; int maxi = (1 << (m + 1));
    for (int i = 1; i <= n; i++) {
        for (int msk = 0; msk < maxi; msk++)
            dp[i][0][msk<<1] += dp[i-1][m][msk];
        for (int j = 1; j <= m; j++) {
            for (int msk = 0; msk < maxi; msk++) {
                int vert = msk & (1<<j), hori = msk & (1<<(j-1));
                if (!vert and !hori) {
                    dp[i][j][msk + (1<<j)] += dp[i][j-1][msk], dp[i][j][msk+(1<<j)] %= mod;
                    dp[i][j][msk + (1<<(j-1))] += dp[i][j-1][msk], dp[i][j][msk+(1<<(j-1))] %= mod;
                } else if (!vert and hori)
                    dp[i][j][msk - hori] += dp[i][j-1][msk], dp[i][j][msk - hori] %= mod;
                else if (vert and !hori)
                    dp[i][j][msk-vert] += dp[i][j-1][msk], dp[i][j][msk-vert] %= mod;
            }
        }
    }
    cout << dp[n][m][0] << endl;
}