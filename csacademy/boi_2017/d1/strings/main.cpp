#include <bits/stdc++.h>
#define mp make_pair

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

ll mod = 1e9 + 9;
ll p = 31;

ll power(ll x, ll pow) {
    if (pow == 0)
        return 1;
    ll half = power(x, pow / 2);
    if (pow % 2)
        half *= (half * x) % mod;
    else
        half *= half;
    return half % mod;
}

ll powp[200000 + 10];
ll powpinv[200000 + 10];
void precalc() {
    powp[0] = 1;
    powpinv[0] = 1;
    for (int i = 1; i < 200010; i++)
        powp[i] = (powp[i - 1] * p) % mod;
    powpinv[1] = power(powp[1], mod - 2);
    for (int i = 2; i < 200010; i++)
        powpinv[i] = (powpinv[i - 1] * powpinv[1]) % mod;
}

ll hash1[(int)2e5 + 10];
ll hash2[(int)2e5 + 10];
int n;

void calchash(string s, int n) {
    hash1[0] = s[0] - 'a';
    for (int i = 1; i < n; i++)
        hash1[i] = (powp[i] * (s[i] - 'a')) % mod, hash1[i] = (hash1[i] + hash1[i - 1]) % mod;
    
    hash2[n - 1] = s[n - 1] - 'a';
    for (int i = n - 2; i >= 0; i--)
        hash2[i] = (powp[(n - i - 1)] * (s[i] - 'a')) % mod, hash2[i] = (hash2[i] + hash2[i + 1]) % mod;
}

ll get_subhash2(int l, int r) {
    if (r == n - 1)
        return hash2[l];
    
    ll h = hash2[l] - hash2[r + 1];
    if (h < 0)
        h += mod;
    h *= powpinv[n - r - 1];
    h %= mod;
    return h;
}

ll get_subhash1(int l, int r) {
    if (l == 0)
        return hash1[r];
    
    ll h = hash1[r] - hash1[l - 1];
    if (h < 0)
        h += mod;
    h *= powpinv[l];
    h %= mod;
    return h;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int q;
    cin >> n >> q;
    string s;
    cin >>s;
    precalc();
    calchash(s, n);

    while (q--) {
        char q;
        cin >> q;

        if (q == 'Q') {
            int l, r;
            cin >> l >> r;
            l--, r--;
            if (get_subhash1(l, r) == get_subhash2(l, r))
                cout << "YES\n";
            else
                cout << "NO\n";
        }
    }
}