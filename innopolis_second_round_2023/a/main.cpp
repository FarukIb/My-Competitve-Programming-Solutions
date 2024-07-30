#include <bits/stdc++.h>
#define mp make_pair
#define all(a) a.begin(), a.end()

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int n, q; ll x;
    cin >> n >> q >> x;

    vector<ll> masses(q);
    for (int i = 0; i < n; i++) {
        int t;
        cin >> t;
        ll m, p;
        cin >> m >> p;
        masses[t - 1] += m * p; 
    }

    sort(all(masses), greater<ll>());
    int i;
    x *= 100;
    for (i = 0; x > 0 && i < q; i++)
        x -= masses[i];
    if (x > 0)
        cout << "-1\n";
    else
        cout << i << "\n";
}