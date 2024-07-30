#include <bits/stdc++.h>
#define mp make_pair

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

const ll mod = 1e9 + 7;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int n;
    cin >> n;
    vector<string> grid(n);
    for (int i = 0; i < n; i++)
        cin >> grid[i];
    
    vector<vector<int> > dp(n + 1, vector<int>(n + 1, 0));
    if (grid[0][0] == '.')
        dp[1][1] = 1;
    
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            if (grid[i - 1][j - 1] != '*')
                dp[i][j] += (dp[i - 1][j] + dp[i][j - 1]) % mod;
    cout << dp[n][n] << "\n";
}