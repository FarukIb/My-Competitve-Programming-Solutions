#include <bits/stdc++.h>
#define pii pair<ll, ll>
#define ll long long
#define ld long double
#define mod 1000000007

using namespace std;

ll shave(ll x) {
    ll clz = 0;
    while (x > 0) {
        if (x % 4 == 0)
            x /= 4;
        else if (x % 2 == 1)
            x /= 2;
        else 
            return x;
    }
    return 0;
}

ll myMod(ll x) {
    x = x % mod;
    if (x < 0)
        x += mod;
    return x;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    ll t; t =1;
    while (t--) {
        ll n, p;
        cin >> n >> p;
        vector<ll> arr(n);
        for (ll i = 0; i < n; i++)
            cin >> arr[i];
        sort(arr.begin(), arr.end());
        
        map<ll, ll> mapp; // first == shaved, second == minimum number of digits before shave
        for (ll i = 0; i < n; i++) {
            ll siz = __lg(arr[i]);
            ll shaved = shave(arr[i]);

            if (mapp.find(shaved) == mapp.end()) {
                mapp[shaved] = siz;
            }
            else {
                mapp[shaved] = min(mapp[shaved], siz);
            }
        }

        vector<ll> dp(max(40LL, p + 1));
        for (pii x : mapp)
            dp[x.second + 1]++;
        dp[1] += dp[0];
        ll ans = dp[0] + dp[1];
        for (ll i = 2; i <= p; i++)
            dp[i] += myMod((dp[i - 1] + dp[i - 2])), ans += dp[i], ans = myMod(ans);

        cout << ans << "\n";
    }
}
