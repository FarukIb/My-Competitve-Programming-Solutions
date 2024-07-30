#include <bits/stdc++.h>
#define mp make_pair

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

const ll mod = 1e9 + 7;
const ll maxn = 1e5 + 10;

vector<vector<int> > factors;
void make_fact() {
    factors.resize(maxn, vector<int>());
    for (int i = 1; i < maxn; i++) {
        for (int j = i; j < maxn; j += i)
            factors[j].push_back(i);
    }
}

vector<ll> factorial;
vector<ll> inv_factorial;

ll bin_expo(ll base, ll exp) {
    if (exp == 0)
        return 1;
    ll half = bin_expo(base, exp / 2);
    half *= half, half %= mod;
    if (exp % 2)
        half *= base, half %= mod;
    return half;
}

ll mod_inv(ll guy) {return bin_expo(guy, mod - 2); }

void precalc_facto() {
    factorial.resize(maxn);
    inv_factorial.resize(maxn);
    factorial[0] = 1, inv_factorial[0] = 1;
    for (int i = 1; i < maxn; i++)
        factorial[i] = (factorial[i - 1] * (ll)i) % mod, inv_factorial[i] = mod_inv(factorial[i]);
}

ll bin_coef(int a, int b) {
     return a >= b ? (((factorial[a] * inv_factorial[b]) % mod) * inv_factorial[a - b]) % mod : 0;
    }

map<pii, ll> ans;
ll recur(ll sum, ll friends) {
    if (sum < friends)
        return 0;
    if (sum == friends)
        return 1;
    if (ans.count(pii(sum, friends)))
        return ans[pii(sum, friends)];
    
    ll out = bin_coef(sum - 1, friends - 1);
    for (int s : factors[sum]) {
        if (s == sum)
            continue;
        out -= recur(s, friends);
        out %= mod;
        if (out < 0)
            out += mod;
    }
    ans[pii(sum, friends)] = out;
    return out;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    make_fact();
    precalc_facto();

    int q;
    cin >> q;
    while (q--) {
        int f, n;
        cin >> n>> f;
        cout << recur(n, f) << "\n";
    }
}