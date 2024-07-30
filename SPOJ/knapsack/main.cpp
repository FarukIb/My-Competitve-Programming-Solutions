#include <bits/stdc++.h>
#define mp make_pair

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int s, n;
    cin >> n >> s;
    vector<pii> items(s);
    for (int i = 0; i < s; i++)
        cin >> items[i].first >> items[i].second;
    
    vector<vector<int> > dp(s + 1, vector<int>(n + 1, 0));
    for (int i = 1; i <= s; i++) {
        int siz = items[i - 1].first, val = items[i - 1].second;
        for (int j = 0; j <= n; j++)
        {
            dp[i][j] = dp[i - 1][j];
            if (j >= siz)
                dp[i][j] = max(dp[i][j], dp[i - 1][j - siz] + val);
        }
    }

    cout << dp[s][n] << "\n";
}