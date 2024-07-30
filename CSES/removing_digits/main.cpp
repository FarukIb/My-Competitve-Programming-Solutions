#include <bits/stdc++.h>
#define mp make_pair
#define all(a) a.begin(), a.end()

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int n;
    cin >> n;
    vector<ll> dp(n+1, 1e18);
    dp[0] = 0;
    for (int i = 1; i <= n; i++) {
        string st = to_string(i);
        for (int j = 0; j < st.size(); j++)
            dp[i] = min(dp[i], 1+dp[i - st[j] + '0']);
    }
    cout << dp[n] << endl;
}