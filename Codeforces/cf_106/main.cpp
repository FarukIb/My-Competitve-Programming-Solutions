#include <bits/stdc++.h>
#define mp make_pair

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

const ll mod = 1e9 + 7;
const ll p = 31;



string s;
int n;

vector<ll> pref_hash;
vector<ll> suff_hash;
vector<ll> pows;
vector<ll> invpow; // 129032259 - 1

vector<ll> get_pref_hashv(string ss) {
    vector<ll> pref_hash;
    int n = ss.size();
    pref_hash.resize(n + 1, 0);
    pref_hash[0] = ss[0] - 'A';
    for (int i = 1; i < n; i++)
        pref_hash[i] = (pref_hash[i - 1] + pows[i] * (ll)(ss[i] - 'A')) % mod;
    return pref_hash;
}

vector<ll> get_suff_hashv(string ss) {
    vector<ll> suff_hash;
    int n = ss.size();
    suff_hash.resize(n + 1, 0);
    suff_hash[n - 1] = ss[n - 1] - 'A';
    for (int i = n - 2; i >= 0; i--)
        suff_hash[i] = (suff_hash[i + 1] + pows[n - i - 1] * (ll)(ss[i] - 'A')) % mod;
    return suff_hash;
}


void precalc() {
    pows.resize(2e5, 0);
    invpow.resize(2e5, 0);
    pows[0] = 1, invpow[0] = 1, pows[1] = p, invpow[1] = 129032259;
    for (int i = 2; i < 2e5; i++)
        pows[i] = (pows[i - 1] * p) % mod, invpow[i] = (invpow[i - 1] * invpow[1]) % mod;
    
    pref_hash = get_pref_hashv(s);
    suff_hash = get_suff_hashv(s);
}

ll get_pref_hash(int l, int r) {
    ll begin = pref_hash[r];
    if (l != 0) {
        begin -= pref_hash[l - 1];
        begin *= invpow[l];
        begin %= mod;
        if (begin < 0)
            begin += mod;
    }
    return begin;
}

ll get_suff_hash(int l, int r) {
    ll begin = suff_hash[l];
    if (r != n - 1) {
        begin -= suff_hash[r + 1];
        begin *= invpow[n - r - 1];
        begin %= mod;
        if (begin < 0)
            begin += mod;
    }
    return begin;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    cin >> s;
    precalc();
    n = s.size();
    pref_hash = get_pref_hashv(s);
    pref_hash = get_pref_hashv(s);

    int m;
    cin >> m;
    int out = 0;
    while (m--) {
        vector<int> pref_vals(n, -1);
        vector<int> suff_vals(n, -1);

        string guy;
        cin >> guy;
        if (guy.size() == 1)
            continue;

        int l = guy.size();
        vector<ll> guy_pref_hash = get_pref_hashv(guy);
        vector<ll> guy_suff_hash = get_suff_hashv(guy);
        // pref calc
        for (int i = 0; i < n; i++) {
            if (s[i] != guy[0])
                continue;
            int k = 0;
            for (int step = l - 1; step > 0; step /= 2) {
                while (k + step < l && i + k + step < n && get_pref_hash(i, i + k + step) == guy_pref_hash[k + step])
                    k += step;
            }
            pref_vals[i] = k;
        }
        // suff calc
        for (int i = n - 1; i >= 0; i--) {
            if (s[i] != guy[l - 1])
                continue;
            int k = 0;
            for (int step = l - 1; step > 0; step /= 2) {
                while (k + step < l && i - k - step >= 0 && get_suff_hash(i - k - step, i) == guy_suff_hash[l - k - step - 1])
                    k += step;
            }
            suff_vals[i] = k;
        }

        vector<int> latest_suff(l + 1, -1);
        vector<int> earliest_pref(l + 1, n + 1);
        for (int i = 0; i < n; i++) {
            if (suff_vals[i] != -1)
                latest_suff[suff_vals[i]] = max(latest_suff[suff_vals[i]], i);
            if (pref_vals[i] != -1)
                earliest_pref[pref_vals[i]] = min(earliest_pref[pref_vals[i]], i);
        }
        for (int i = l - 2; i >= 0; i--)
            earliest_pref[i] = min(earliest_pref[i], earliest_pref[i + 1]);
        for (int i = l - 2; i >= 0; i--)
            latest_suff[i] = max(latest_suff[i], latest_suff[i + 1]);

        bool possible = false;
        if (earliest_pref[l - 1] != n + 1 || latest_suff[l - 1] != - 1)
            possible = true;
        for (int i = 0; i < l - 1; i++) {
            if (earliest_pref[i] + i < latest_suff[l - i - 2] - (l - i - 1))
                possible = true;
        }
        if (possible)
            out++;
    }
    cout << out << "\n";
}