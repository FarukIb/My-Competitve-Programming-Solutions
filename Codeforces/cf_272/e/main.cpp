#include <bits/stdc++.h>
#define mp make_pair

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

const int INF = 1e7;

int getA(string s, string p, int i) {
    int pnt = 0; int out = 0;
    for (int j = i; j < s.size(); j++) {
        if (s[j] == p[pnt])
        {
            pnt++;
            if (pnt == p.size() )
                return out;
        }
        else
            out++;
    }
    return INF;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    string s, p;
    cin >> s >> p;
    int n = s.size(), m = p.size();

    vector<int> a(n + 1, 0);
    for (int i = 0; i < n; i++) 
        a[i] = getA(s, p, i);
    
    vector<vector<int> > dp(n + 1, vector<int>(n + 1, 0));

    vector<int> jmax(n + 1, 0);
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= i; j++)
        {
            if (i != n)
                dp[i + 1][j] = max(dp[i][j], dp[i + 1][j]);
            
            if (i != n && j != n)
                dp[i + 1][j + 1] = max(dp[i][j], dp[i + 1][j + 1]);
            
            int i2 = i + a[i] + m, j2 = j + a[i];
            if (i2 > n || j2 > n)
                continue;
            dp[i2][j2] = max(dp[i2][j2], dp[i][j] + 1);
        }
    }

    for (int i = 0; i < n; i++)
        cout << dp[n][i] << " ";
    cout << "0\n";
}