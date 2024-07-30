#include <bits/stdc++.h>
#define mp make_pair
#define all(a) a.begin(), a.end()

using namespace std;

typedef unsigned long long ll;
typedef __uint128_t LL;
typedef pair<int, int> pii;

LL get_num(LL tim, vector<ll> &guysssss) {
    LL sum = 0;
    for (ll a : guysssss)
        sum += (LL)tim / (LL)a;
    return sum;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    ll n, t;
    cin >> n >> t;
    vector<ll> guyssss(n);
    for (int i = 0; i < n; i++)
        cin >> guyssss[i];
    
    LL l = 0, r = 4e18; ll ans = 0;
    while (l < r) {
        LL mid = (l + r) / 2;
        if (get_num((LL)mid, guyssss) >= t)
            r = mid, ans = mid;
        else
            l = mid + 1;
    }

    cout << ans << endl;
}