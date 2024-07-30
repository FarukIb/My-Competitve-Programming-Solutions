#include <bits/stdc++.h>
#define mp make_pair
#define all(a) a.begin(), a.end()

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    string a, b;
    cin >> a >> b;
    int n, m;
    n = a.size(), m = b.size();
    vector<vector<int> > dp(n + 1, vector<int>(m + 1));
    int out = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
            if (a[i - 1] == b[j - 1])
                dp[i][j] = max(dp[i][j], dp[i - 1][j - 1] + 1);
            out = max(out, dp[i][j]);
        }
    }
    cout <<out << "\n";
}