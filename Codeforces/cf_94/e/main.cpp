#include <bits/stdc++.h>
#define mp make_pair

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

const ll mod = 1e9 + 7;
const ll maxn = 1010;

ll bin_expo(ll base, ll expo) {
    if (expo == 0)
        return 1;
    ll half = bin_expo(base, expo / 2);
    half *= half; half %= mod;
    if (expo % 2)
        half *= base, half %= mod;
    return half;
}

ll fact[maxn];
ll invfact[maxn];

void precompute() {
    fact[0] = 1, invfact[0] = 1;
    for (ll i = 1; i < maxn; i++) {
        fact[i] = fact[i - 1] * i;
        fact[i] %= mod;

        invfact[i] = bin_expo(fact[i], mod - 2);
    }
}

ll bin_coef(ll n, ll k) {
    if (n < k)
        return 0;
    return ((fact[n] * invfact[k]) % mod * invfact[n - k]) % mod;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    precompute();

    ll n, m, k;
    cin >> n >> m >> k;

    ll out = bin_coef(n - 1, 2 * k) * bin_coef(m - 1, 2 * k) % mod;
    cout << out << "\n";
}