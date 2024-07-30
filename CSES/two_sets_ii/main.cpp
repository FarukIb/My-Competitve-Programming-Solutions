#include <bits/stdc++.h>
#define mp make_pair
#define all(a) a.begin(), a.end()

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

const ll mod = 1e9 + 7;
const ll inv = 500000004;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int n;
    cin >> n;
    int sum = n * (n + 1) / 2;
    if (sum % 2) {
        cout << "0\n";
        return 0;
    }
    vector<ll> dp(sum, 0); dp[0] = 1;
    vector<ll>my(sum, 0);
    for (int i = 1; i <= n; i++) {
        fill(all(my), 0);
        for (int j = 0; j < sum; j++) {
            my[j] = dp[j];
            if (j >= i)
                my[j] += dp[j - i], my[j] %= mod;
        }
        dp = my;
    }
    dp[sum / 2] *= inv, dp[sum / 2] %= mod;
    cout << dp[sum / 2] << "\n";
}