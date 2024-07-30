#include <bits/stdc++.h>
#define mp make_pair

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

ll dp[101][110*26];
const int maxn = 100;
const int max_d = 25;
const ll mod = 1e9 + 7;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    for (int i = 0; i <= 25; i++)
        dp[1][i] = 1;
    for (int i = 2; i <= maxn; i++) {
        for (int j = 0; j <= max_d * i; j++)
            for (int k = j; k >= max(0, j - max_d); k--)
                dp[i][j] += dp[i - 1][k], dp[i][j] %= mod;
    }

    int t;
    cin >> t;
    while (t--) {
        string s;
        cin >> s;
        int sum = 0;
        for (int i = 0; i < s.size(); i++)
            sum += s[i] - 'a';
        cout << dp[s.size()][sum] - 1 << "\n";
    }
}