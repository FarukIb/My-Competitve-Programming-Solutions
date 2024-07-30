#include <bits/stdc++.h>
#define mp make_pair
#define all(a) a.begin(), a.end()

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    ll n;
    cin >> n;
    ll sum = 0;
    map<ll, ll> guyy;
    for (int i = 0; i < n; i++) {
        ll p;
        cin >> p;
        sum += p;
        guyy[p]++;
    }

    int q;
    
    ll con = 0;
    cin >> q;
    while (q--) {
        string t;
        cin >> t;
        if (t == "INFLATION") {
            ll val;
            cin >> val;
            sum += n * val;
            con += val;
        } else {
            ll idx, neww;
            cin >> idx >> neww;
            if (idx != neww)
            {
                sum += guyy[idx - con] * (neww - idx);
                guyy[neww - con] += guyy[idx - con];
                guyy[idx - con] = 0;
            }
        }
        cout << sum << "\n";
    }
}