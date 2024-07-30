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

    int n, x;
    cin >> n >> x;
    vector<ll> dp(x+1); dp[0] = 1;
    vector<int> coins(n);
    for (int i = 0; i< n; i++)
        cin >> coins[i];
    for (int i = 1; i <= x; i++)
        for (int j = 0; j < n; j++)
            if (i - coins[j] >= 0)
                dp[i] += dp[i - coins[j]], dp[i] %= mod;
    cout << dp[x] << endl;
}