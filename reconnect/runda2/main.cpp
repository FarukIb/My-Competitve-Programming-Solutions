#include <bits/stdc++.h>
#define mp make_pair

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int n, m;
    cin >>n >>m;
    vector<vector<int> > mat(n, vector<int>(m, 0));
    for (int i = 0; i < n; i++)
        for (int j = 0; j <m; j++)
            cin >> mat[i][j];

    vector<vector<int> > dp(n, vector<int>(m, 0));
    
    int x, y;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++)
            if (mat[i][j] == 0)
                x = i, y = j;
    }

    for (int i = x; i < n; i++) {
        for (int j = y; j <m; j++) {
            if (i - x > 0)
                dp[i][j] = max(dp[i][j], mat[i][j] + dp[i - 1][j]);
            if (j - y > 0)
                dp[i][j] = max(dp[i][j], mat[i][j] + dp[i][j - 1]);
        }
    }

    for (int i = x; i >= 0; i--) {
        for (int j = y; j >= 0; j--) {
            if (i != x)
                dp[i][j] = max(dp[i][j], mat[i][j] + dp[i + 1][j]);
            if (j != y)
                dp[i][j] = max(dp[i][j], mat[i][j] + dp[i][j + 1]);
        }
    }

    cout << dp[n - 1][m - 1] + dp[0][0] << endl;
}