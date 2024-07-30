#include <bits/stdc++.h>
#define pii pair<int, int>
#define ll __int128
#define ld long double

using namespace std;

ll expo(ll mod, ll base, ll exp) {
    if (exp == 0)
        return 1;
    
    ll half = expo(mod, base, exp / 2);
    half *= half;
    half %= mod;
    if (exp % 2)
        half *= base, half %= mod;
    return half;
}

ll mymod(ll a, ll mod) {
    a %= mod;
    if (a < 0)
        a += mod;
    return a;
}

bool is_prime(ll x) {
    if (x % 2 == 0)
        return false;
    ll realX = x;

    x--;
    ll s = 0;
    while (x % 2 == 0)
        x /= 2, s++;

    for (ll base : vector<ll>({2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41}))
    {
        if (realX == base)
            return true;

        bool good = false;
        ll curr = expo(realX, base, x);
        if ((curr + 1) % realX == 0)
            continue;
        for (ll i = 0; i < s; i++) {
            if (mymod(curr - 1, realX) == 0)
            {
                good = true;
                break;
            }
            curr *= curr;
            curr %= realX;
        }
        if (mymod(curr - 1, realX) == 0)
            good = true;
        if (!good)
           return false; 
    }
    return true;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    long long N;
    cin >> N;
    if (N == 1 || N == 2)
    {
        cout << 2 << "\n";
        return 0;
    }
    ll n = N;

    while (1) {
        if (is_prime(n++)) {
            cout << (long long)(n - 1) << "\n";
            break;
        }
    }
}
