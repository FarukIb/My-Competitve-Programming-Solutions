#include <bits/stdc++.h>
#define mp make_pair
#define all(a) a.begin(), a.end()

using namespace std;

typedef long long ll;
typedef pair<ll, ll> pii;

const ll mod = 1e9 + 7;
const int maxn = 1e6+1;

ll gcd_extended(ll a, ll b, ll &x, ll &y) {
    if (b == 0) {
        x = 1, y = 0;
        return a;
    }

    ll gc = gcd_extended(b, a % b, x, y);
    ll X = x;
    x = y;
    y = X - (a / b) * y;
    return gc;
}

ll mod_inv(ll a) {
    ll x, y;
    ll gc = gcd_extended(a, mod, x, y);
    return (x + mod) % mod;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    vector<ll> fact(maxn);
    fact[0] = 1;
    for (int i = 1; i < maxn; i++)
        fact[i] = fact[i - 1] * i % mod;
    
    int n;
    cin >> n;
    while (n--) {
        int a, b;
        cin >> a >> b;
        if (b> a)
        {
            cout << "0\n";
            continue;
        }
        ll A = fact[a];
        ll B = mod_inv(fact[b]);
        ll C = mod_inv(fact[a - b]);
        cout << A * B % mod * C % mod << "\n";
    }
}