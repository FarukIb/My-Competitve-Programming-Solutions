#include <bits/stdc++.h>
#define mp make_pair

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

ll process(ll m, ll curr) {
    if (curr % 2 == 0)
        return 0;
    ll out = 0;
    for (ll a = curr; a < m; a *= 2)
        out += m - a;
    return out;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int n, m;
    cin >> n >> m;
    int gcd = -1;
    for (int i = 0; i < n; i++) {
        int s;
        cin >> s;
        s--;
        if (gcd == -1)
            gcd = s;
        else
            gcd = __gcd(gcd, s);
    }

    ll out = 0;
    for (int i = 1; i * i <= gcd; i++) {
        if (gcd % i != 0)
            continue;
        
        int q = gcd / i;
        out += process(m, i);
        if (q != i)
            out += process(m, q);
    }

    cout << out << "\n";
}