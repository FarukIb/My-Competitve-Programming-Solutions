#include <bits/stdc++.h>
#define ll long long
#define ld long double
#define pll pair<ll, ll>

using namespace std;

ll myPow(int xp) {
    ll base = 1;
    for (int i = 0; i < xp; i++)
        base *= 10LL;
    return base;
}

ll inter(pll a, pll b) {
    if (a.first > b.first || a.first == b.first && a.second < b.second)
        swap(a, b);

    if (a.second < b.first)
        return 0;

    if (b.second <= a.second)
        return b.second - b.first + 1;


    return a.second - b.first + 1;
}

int main() {
    int n, k;
    cin >> n;
    vector<pll > intervals(n + 1);
    for (int i = 0; i < n; i++)
        cin >> intervals[i + 1].first >> intervals[i + 1].second;
    cin >> k;
    if (k == 0) {
        cout << 1 << endl;
        return 0;
    }

    vector<pll> goodIntervals;
    for (int i = 0; i <= 18; i++)
        goodIntervals.push_back(pll(myPow(i), myPow(i) * 2 - 1));
    

    vector<ll> good(n + 1, 0);
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j <= 18; j++)
            good[i] += inter(goodIntervals[j], intervals[i]);
    }

    vector<ld> prob(n + 1);
    for (int i = 1; i <= n; i++)
        prob[i] = (ld)good[i] / ((ld)intervals[i].second - (ld)intervals[i].first + 1);

    // PHASE 2
    vector<vector<ld> > dp(n + 1, vector<ld>(n + 1, 0));
    dp[0][0] = 1;
    for (int i = 1; i <= n; i++) {
        dp[i][0] = dp[i - 1][0] * (1 - prob[i]);
        for (int j = 1; j <= n; j++) {
            dp[i][j] = prob[i] * dp[i - 1][j - 1] + (1 - prob[i]) * dp[i - 1][j];
        }
    }

    ld out = 0;
    for (int j = 0; j <= n; j++)
        if ((ld)j / (ld)n - (ld)k / 100.0 > -1e-11)
            out += dp[n][j];
    cout << fixed << setprecision(17) << out << endl;
}