#include <bits/stdc++.h>
#define mp make_pair
#define all(a) a.begin(), a.end()

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    freopen ("cowmbat.out","w",stdout);
    freopen ("cowmbat.in","r",stdin);

    int n, k, s;
    cin >> n >> s >> k;
    string str;
    cin >> str;
    str.insert(str.begin(), '0');
    vector<vector<ll> > cost(s, vector<ll>(s));
    for (int i = 0; i < s; i++)
        for (int j = 0; j < s; j++)
            cin >> cost[i][j];
    for (int k = 0; k < s; k++)
        for (int i = 0; i < s; i++)
            for (int j = 0; j < s; j++)
                cost[i][j] = min(cost[i][j], cost[i][k] + cost[k][j]);

    vector<vector<ll> > prefcost(n+1, vector<ll>(s+1));
    for (int i = 0; i < s; i++) {
        for (int j = 1; j <= n; j++)
            prefcost[j][i] = prefcost[j - 1][i] + cost[str[j] - 'a'][i];
    }
    
    vector<vector<ll> >dp(n+1,vector<ll>(s+1, (ll)1e18));
    dp[0][s] = 0;
    for (int i = k; i <= n; i++) {
        for (int j = 0; j < s; j++) {
            dp[i][j] = dp[i - 1][j] + cost[str[i] - 'a'][j];
            ll cst = prefcost[i][j] - prefcost[i - k][j];
            dp[i][j] = min(dp[i][j], *min_element(all(dp[i - k])) + cst);
        }
    }

    cout << *min_element(all(dp[n])) << "\n";
}