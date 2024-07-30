#include <bits/stdc++.h>
#define mp make_pair

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

const ll mod = 1e9 + 7;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int n, a, b, k;
    cin >> n >> a >> b >> k;
    if (b < a) // flip
        swap(a, b);

    vector<vector<ll> > dp(n + 1, vector<ll>(k + 1, 0));
    dp[a][0] = 1;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= k; j++) {
            dp[i][j] = dp[i - 1][j - 1];
        }
    }
}