#include <bits/stdc++.h>
#define mp make_pair
#define all(a) a.begin(), a.end()

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

ll get_alpha(ll n, ll p) {
    ll out = 0;
    for (ll d = p; d <= n; d *= p)
        out += n / d;
    return out;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    ll n;
    cin >> n;
    cout << get_alpha(n, 5) << endl;
}