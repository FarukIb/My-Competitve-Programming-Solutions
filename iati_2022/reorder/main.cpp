#include <bits/stdc++.h>
#define mp make_pair
#define all(a) a.begin(), a.end()

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int n, q; ll A;
    cin >> n >> q >> A; 
    vector<ll> arr(n + 1);
    for (int i = 1; i <= n; i++)
        cin >> arr[i];

    while (q--) {
        int r;
        cin >> r;
        ll mini = 1e18;
        for (int mask = 0; mask < (1 << n); mask++) {
            int cnt1 = 0, cnt2 = 0;
            for (int i = 0; i < r; i++)
                if ((1 << i) & mask)
                    cnt1++;
            for (int i = r; i < n; i++)
                if ((1 << i) & mask)
                    cnt2++;
            if (cnt1 != cnt2)
                continue;
            bitset<20> chosen(mask);
            ll sum = 0;
            int so_far = 0;
            for (int i = 0; i < r; i++) {
                if (chosen[i]) {
                    sum += (cnt1 + (r - i - 1) - so_far) * arr[i];
                    so_far++;
                }
                else
                    sum += arr[i] * so_far + arr[i] * A;
            }
            so_far = 0;
            for (int i = n - 1; i >= r; i++) {
                if (chosen[i]) {
                    sum += (cnt1 + A + (i - r) - so_far) * arr[i];
                    so_far++;
                } else {
                    sum += arr[i] * so_far;
                }
            }
            mini = min(mini, sum);
        }
    }
    
    /*vector<vector<vector<ll> > > pref_dp(n + 2, vector<vector<ll> > (n + 2, vector<ll> (n + 2, 1e18)));
    vector<vector<vector<ll> > > suf_dp = pref_dp;
    for (int d = 0; d <= n; d++)
    {
        pref_dp[d][0][0] = 0;
        for (int i = 1; i <= n; i++)
        {
            for (ll s = 0; s <= d; s++) 
            {
                pref_dp[d][i][s] = pref_dp[d][i - 1][s] + arr[i] * s;
                if (s > 0)
                    pref_dp[d][i][s] = min(pref_dp[d][i][s], pref_dp[d][i - 1][s - 1] - arr[i] * A + arr[i] * d);
            }
        }
    }

    for (int d = 0; d <= n; d++)
    {
        suf_dp[d][n + 1][0] = 0;
        for (int i = n; i >= 1; i--)
        {
            for (ll s = 0; s <= d; s++) 
            {
                suf_dp[d][i][s] = suf_dp[d][i + 1][s] + arr[i] * s;
                if (s > 0)
                    suf_dp[d][i][s] = min(suf_dp[d][i][s], suf_dp[d][i + 1][s - 1] + arr[i] * A + arr[i] * d);
            }
        }
    }

    while (q--) {
        int r;
        cin >> r;
        ll out = 1e18;
        ll og_val = 0;
        for (int i = 1; i <= r; i++)
            og_val += arr[i] * A;
        out = og_val;

        for (ll d = 0; d < n; d++)
            out = min(out, og_val + pref_dp[d][r][d] + suf_dp[d][r + 1][d]);
        cout << out << "\n";
    }*/
}