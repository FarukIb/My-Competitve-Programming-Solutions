#include <bits/stdc++.h>
#define mp make_pair
#define all(a) a.begin(), a.end()

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

const ll mod = 1e9+7;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int n;
    cin >> n;
    vector<ll> dp(n+1); dp[0] = 1;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; i - j >= 0 and j <= 6; j++)
            dp[i] += dp[i - j], dp[i] %= mod;
    }
    cout << dp[n] << endl;
}