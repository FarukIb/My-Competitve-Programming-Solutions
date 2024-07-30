#include <bits/stdc++.h>
#define mp make_pair

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

const ll mod = 1e9 + 7;

ll fact[100];
ll invfact[100];

ll bin_expo(ll base, ll expo) {
    if (expo == 0)
        return 1;
    ll half = bin_expo(base, expo / 2);
    half *= half, half %= mod;
    if (expo % 2)  
        half *= base, half %= mod;
    return half;
}

void precomp() {
    fact[0] = 1, invfact[0] = 1;
    for (ll i = 1; i < 100; i++)
        fact[i] = fact[i - 1] * i % mod, invfact[i] = bin_expo(fact[i], mod - 2);
}

ll bin_coef(int n, int k) {
    if (n < k)
        return 0;
    return (((fact[n] * invfact[k]) % mod) * invfact[n - k]) % mod;
}

ll dp[2][51][51];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    precomp();

    int n, K;
    cin >> n >> K;
    K /= 50;
    int ones = 0, twos = 0;
    for (int i = 0; i < n; i++) {
        int a;
        cin >> a;
        a /= 50;
        if (a == 1)
            ones++;
        else
            twos++;
    }

    dp[0][ones][twos] = 1;
    int done = -1;
    for (int T = 0; T < 4*n; T++) {
        int side = T % 2;
        for (int o = 0; o <= ones; o++) {
            for (int t = 0; t <= twos; t++) {
                for (int co = 0; co <= o; co++) {
                    for (int ct = 0; ct <= t and co + ct*2 <= K; ct++) {
                        if (co == ct and co == 0)
                            continue;
                        dp[1 - side][ones - o + co][twos - t +ct] += dp[side][o][t] * bin_coef(o, co) % mod * bin_coef(t, ct) % mod;
                        dp[1 - side][ones - o + co][twos - t +ct] %= mod;
                    }
                }
            }
        }
        if (dp[1][ones][twos]) {
            cout << T + 1 << "\n" << dp[1][ones][twos] << "\n";
            return 0;
        }
        if (dp[0][0][0]) {
            cout << T + 1 <<"\n" << dp[0][0][0] << "\n";
            return 0;
        }
    }

    cout << "-1\n0\n";
}