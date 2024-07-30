#include <bits/stdc++.h>
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
    vector<int> arr(n);
    for (int i = 0; i < n; i++)
        cin >> arr[i];
    
    vector<vector<ll> > dp(n, vector<ll>(m + 2, 0));
    if (arr[0] == 0)
        for (int i = 1; i <= m; i++)
            dp[0][i] = 1; 
    
    if (arr[0] != 0)
        dp[0][arr[0]] = 1;
    
    for (int i = 1; i < n; i++) {
        if (arr[i] == 0) {
            for (int j = 1; j <= m; j++)
                dp[i][j] = (dp[i - 1][j - 1] + dp[i - 1][j] + dp[i - 1][j + 1]) % mod;
        }
        else {
            dp[i][arr[i]] = (dp[i - 1][arr[i] - 1] + dp[i - 1][arr[i]] + dp[i - 1][arr[i] + 1]) % mod;
        }
    }

    ll out = 0;
    for (int i = 1; i <= m; i++)
        out += dp[n - 1][i], out %= mod;
    cout << out << "\n";
}