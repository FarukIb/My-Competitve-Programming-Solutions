#include <bits/stdc++.h>
#define mp make_pair
#define all(a) a.begin(), a.end()

using namespace std;

typedef long long ll;
typedef pair<ll, ll> pii;

const ll reg_size = 44;

const ll mod = 1e9 + 7;
const ll p = 29;

ll decode(ll l, string &s) {
    ll out = 0;
    for (ll b = 0; b < reg_size; b++)
        if (s[l + b] == '1')
            out += (1LL << (reg_size - 1 - b));
    return out;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    vector<ll> p_pow(1e6+1);
    p_pow[0] = 1;
    for (int i = 1; i <= 1e6; i++)
        p_pow[i] = p_pow[i - 1] * p % mod;

    int R;
    cin >> R;
    if (R == 1) {
        ll n;
        cin >> n;
        vector<ll> perm(n);
        for (int i = 0; i < n; i++)
            cin >> perm[i];
        string out = "", out2 = "";
        for (ll b = 0; b < reg_size/2; b++) {
            ll sum = 0; ll hash = 0;
            for (ll i = 0; i < n; i++)
                if ((i & (1LL << b)) != 0)
                    sum += perm[i], hash += (perm[i] * p_pow[i]) % mod, hash %= mod;
            out += bitset<reg_size>(sum).to_string();
            out2 += bitset<reg_size>(hash).to_string();
        }
        cout << out + out2 << endl;

        return 0;
    }
    ll n;
    cin >> n;
    vector<ll> perm(n);
    for (ll i = 0; i < n; i++)
        cin >> perm[i];
    
    string S;
    cin >> S;
    string s = "", h = "";
    for (ll i = 0; i < S.size() / 2; i++)
        s += S[i];
    for (ll i = s.size(); i < S.size(); i++)
        h += S[i];

    vector<ll> sums(reg_size/2);
    vector<ll> hashes(reg_size/2);
    for (ll i = 0; i < s.size(); i += reg_size) {
        sums[i / reg_size] = decode(i, s);
        hashes[i / reg_size] = decode(i, h);
    }

    vector<ll> msums(reg_size), mhashes(reg_size);
    for (ll b = 0; b < reg_size/2; b++) {
        ll sum = 0; ll hash = 0;
        for (ll i = 0; i < n; i++)
            if ((i & (1LL << b)) != 0)
                sum += perm[i], hash += (perm[i] * p_pow[i]) % mod, hash %= mod;
        msums[b] = sum;
        mhashes[b] = hash;
    }

    ll sum = n*(n + 1) / 2LL;
    ll f = 0, sec = 0;
    for (ll i = 0; i < reg_size/2; i++) {
        ll my_have_sum = msums[i], my_dont_have = sum - msums[i];
        ll have_sum = sums[i], dont_have = sum - sums[i];

        if (my_have_sum == have_sum) {
            if (hashes[i] != mhashes[i])
                f += 1 << i, sec += 1 << i;
        } else {
            if (my_have_sum < have_sum)
                f += 1 << i;
            else
                sec += 1 << i;
        }
    }
    swap(perm[f], perm[sec]);
    for (ll i = 0; i < n; i++)
        cout << perm[i] << " ";
    cout << endl;
}