#include <bits/stdc++.h>
#define mp make_pair

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

const int maxn = 1e6 + 10;
const ll mod = 1e9 + 7;

ll binexpo(ll base, ll expo) {
    if (expo == 0)
        return 1;
    ll val = binexpo(base, expo/2);
    val *= val, val %= mod;
    if (expo % 2)
        val *= base, val %= mod;
    return val;
}

ll modinv(ll guy) {
    return binexpo(guy, mod - 2);
}

vector<ll> facto;
vector<ll> invfacto;

void precalc() {
    facto.resize(maxn);
    invfacto.resize(maxn);

    facto[0] = 1, invfacto[0] = 1;
     for (ll i = 1; i < maxn; i++)
        facto[i] = (facto[i - 1] * i) % mod, invfacto[i] = modinv(facto[i]);
}

ll bincoef(ll n, ll k) {
    return ((facto[n] * invfacto[k]) % mod * invfacto[n - k]) % mod;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    precalc();

    ll n, a, b, d;
    while (cin >> n >> a >> b >> d)
    {
        cout << (bincoef(n, a) * binexpo(bincoef(b, d), a)) % mod << endl;
    }
    
}