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

    int n, x;
    cin >> n >> x;
    vector<int> w(n), c(n);
    for (int i = 0; i < n; i++)
        cin >> w[i];
    for (int i = 0; i < n; i++)
        cin >> c[i];
    vector<ll> dp(x+1, -1e18);
    dp[0] = 0;
    for (int i = 0; i < n; i++)
        for (int j = x-w[i]; j >= 0; j--)
            dp[j+w[i]] = max(dp[j+w[i]], dp[j] + c[i]);
    cout << *max_element(all(dp)) << endl;
}