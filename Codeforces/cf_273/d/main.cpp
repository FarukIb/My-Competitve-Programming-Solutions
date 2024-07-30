#include <bits/stdc++.h>
#define mp make_pair
#define all(a) a.begin(), a.end()

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

const ll mod = 1e9 + 7;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    ll r, g;
    cin >> r >> g;

    ll height = 0;
    for (ll l = 1; l <= 1e9; l++) {
        if (l * (l+1) / 2LL > r + g)
        {
            height = l - 1;
            break;
        }
    }
    
    
    vector<ll> lastdp(g + 1);
    vector<ll> mydp(g + 1);
    lastdp[0] = 1;

    for (ll l = 1; l <= height; l++) {
        for (ll used = 0; used <= min(g, l*(l+1LL)/2LL); used++) {
            ll gleft = g - used;
            ll rleft = r-(l * (l - 1LL) / 2LL - used);

            if (used >= l)
                mydp[used] = lastdp[used - l];
            if (rleft >=l)
                mydp[used] += lastdp[used], lastdp[used] %= mod;
        }
        swap(mydp, lastdp);
        fill(all(mydp), 0);
    }

    
    cout << accumulate(all(lastdp), 0LL) % mod << "\n";
}