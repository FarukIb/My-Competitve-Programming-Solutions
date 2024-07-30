#include <bits/stdc++.h>
#define mp make_pair

using namespace std;

typedef long long ll;
typedef pair<ll, ll> pii;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    ll q;
    cin >>q;
    while (q--) {
        ll t, k, v;
        cin >> t >> k >> v;
        ll n = 1LL << k;
        if (t == 1) {
            ll x = (v - 1LL) / n + 1;
            ll y = (v - 1LL) % n + 1;
            ll pos = 0;

            for (ll s = 0; s < k * 2; s++) {
                ll siz = 1LL << s;
                if (s % 2)  {
                    // fold up
                    if (y > n / 2)
                        y = n - y + 1, pos = siz + (siz - pos - 1);
                    n /= 2;
                }
                else {
                    if (x > n / 2)
                        x = n - x + 1, pos = siz + (siz - pos - 1);
                }
            }

            cout << pos + 1LL << "\n";
        }
        else {
            ll x = 1, y = 1, siz2 = 2;
            for (ll s = 0; s < k * 2; s++) {
                ll siz = 1LL << (2 * k - s);
                if (v > siz / 2) {
                    if (s % 2 == 0)
                        x = siz2 - x + 1, v = siz - v + 1;
                    else
                        y = siz2 - y + 1, v = siz - v + 1;
                }
                if (s % 2)
                    siz2 *= 2LL;
            }

            cout << (y - 1LL) * n + x << "\n";
        }
    }
}