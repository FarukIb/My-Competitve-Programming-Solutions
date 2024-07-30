#include <bits/stdc++.h>
#define pii pair<ll, ll>
#define ll unsigned long long
#define ld long double

using namespace std;

ll myPow(ll base, ll xp) {
    ll out = 1;
    for (ll i = 0; i < xp; i++)
        out *= base;
    return out;
}

ll powten[19];
ll dp[1 << 19][101];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    for (ll i = 0; i < 19; i++)
        powten[i] = myPow(10, i);

    ll n, m;
    cin >> n >> m;

    ll numDigs = floor(log10(n)) + 1;
    vector<pii> masks;
    for (ll i = 0; i < (1 << numDigs); i++) {
        masks.push_back({__builtin_popcount(i), i});
    }

    string arrr = to_string(n);
    vector<ll> arr;
    for (ll i = 0; i < numDigs; i++)
        arr.push_back(arrr[i] - '0');
    sort(masks.begin(), masks.end());
    dp[0][0] = 1;
    for (pii x : masks) {
        ll mask = x.second;

        for (ll mod = 0; mod < m; mod++) {
            if (dp[mask][mod] == 0)
                continue;
            for (ll i = 0; i < numDigs; i++) {
                if ((1 << i) & mask || x.first == numDigs - 1 && arr[i] == 0)
                    continue;
                dp[mask | (1 << i)][(mod + arr[i] * powten[x.first]) % m] += dp[mask][mod];
            }
        }
    }


    ll out = dp[(1 << (numDigs)) - 1][0];
    sort(arr.begin(), arr.end());
    ll cnt = 1;
    for (ll i = 1; i < numDigs; i++) {
        if (arr[i] == arr[i - 1])
            cnt++;
        else 
            cnt = 1;
        out /= cnt;
    }
    cout << out << "\n";
}
