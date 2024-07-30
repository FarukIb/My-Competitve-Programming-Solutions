#include <bits/stdc++.h>
#define mp make_pair

using namespace std;

typedef long long ll;
typedef pair<ll, ll> pii;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    ll n, a, b;
    cin >> n >> a >> b;

    ll x = a / __gcd(a, b + 1);
    x *= b;

    vector<pii> arr;
    for (int i = 0; i < n; i++) {
        ll l, r;
        cin >> l >> r;

        if (r - l + 1 >= x) {
            arr.push_back(mp(0, x - 1));
            continue;
        }

        l %= x;
        r %= x;

        if (l <= r)
            arr.push_back(mp(l, r));
        else
            arr.push_back(mp(0, r)), arr.push_back(mp(l, x - 1));
    }
    sort(arr.begin(), arr.end());

    ll l = arr[0].first, r = arr[0].second;
    ll out = 0;
    for (int i = 1; i < arr.size(); i++) {
        if (arr[i].first > r) {
            out += r - l + 1;
            l = arr[i].first, r = arr[i].second;
        }

        r = max(r, arr[i].second);
    }
    
    out += r - l + 1;

    cout << out << "\n";
}