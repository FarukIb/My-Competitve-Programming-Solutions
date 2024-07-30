#include "boxes.h"
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int n, k, lll;

long long delivery(int N, int K, int L, int p[]) {
    n = N, k = K, lll = L;

    vector<ll> l(N + 1, 0);
    l[0] = p[0];
    vector<ll> r(N + 1, 0);
    r[n - 1] = (ll)(L - p[n - 1]);

    for (int i = 0; i < n; i++) {
        if (i < k) {
            l[i] = (ll)p[i] * 2LL;
        }
        else {
            l[i] = l[i - k] + (ll)p[i] * 2LL;
        }
    }

    for (int i = n - 1; i >= 0; i--) {
        if (i + k >= n) {
            r[i] = 2LL * ((ll)L - (ll)p[i]);
        }
        else {
            r[i] = r[i + k] + ((ll)L - p[i]) * 2LL;
        }
    }


    ll mini = min(l[n - 1], r[0]);
    if (K == N)
        mini = min((ll)L, mini);
    for (int i = 0; i < n - 1; i++)
        mini = min(mini, l[i] + r[i + 1]);

    for (int i = 0; i < n - k; i++)
        mini = min(mini, l[i] + (ll)L + r[i + k + 1]);

    return mini;
}
