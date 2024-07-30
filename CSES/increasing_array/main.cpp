#include <bits/stdc++.h>
#define mp make_pair
#define all(a) a.begin(), a.end()

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int n;
    cin >> n;
    ll f; cin >> f; ll sum = 0;
    for (int i = 1; i < n; i++) {
        ll s; cin >> s;
        ll ns = max(s, f);

        sum += ns - s;
        f = ns;
    }

    cout << sum << endl;
}