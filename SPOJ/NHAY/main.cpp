#include <bits/stdc++.h>
#define mp make_pair
#define all(a) a.begin(), a.end()

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

const ll p = 31;
const ll mod = 1e9 + 7;
const ll maxn = 1e6+1;

vector<ll> pow_p(maxn), inv_pow_p(maxn);

ll bin_expo(ll base, ll xp) {
    if (xp == 0)
        return 1;
    ll half = bin_expo(base, xp / 2);
    half = half * half % mod;
    if (xp % 2)
        half = half * base % mod;
    return half;
}

void init() {
    pow_p[0] = 1;
    for (ll i = 1; i < maxn; i++)
        pow_p[i] = pow_p[i - 1] * p % mod;
    inv_pow_p[maxn - 1] = bin_expo(pow_p[maxn - 1], mod - 2);
    for (ll i = maxn - 2; i >= 0; i--)
        inv_pow_p[i] = inv_pow_p[i + 1] * p % mod;
}

vector<ll> get_hash(string s) {
    int n = s.size();
    vector<ll> hash(n);
    for (int i = 0; i < n; i++) {
        hash[i] = (s[i] - 'a') * pow_p[i] % mod;
        if (i != 0)
            hash[i] = (hash[i - 1] + hash[i]) % mod;
    }
    return hash;
}

ll get_substr_hash(int l, int r, vector<ll> &hash) {
    ll curr = hash[r];
    if (l != 0)
        curr = (curr - hash[l - 1] + mod) % mod;
    curr = (curr * inv_pow_p[l]) % mod;
    return curr;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    init();

    int n;
    while (cin >> n) {
        string needle, haystack;
        cin >> needle >> haystack;
        vector<ll> hash1 = get_hash(needle), hash2 = get_hash(haystack);
        for (int i = 0; i + n <= haystack.size(); i++) 
            if (hash1.back() == get_substr_hash(i, i + n - 1, hash2))
                cout << i << "\n";
    }
}