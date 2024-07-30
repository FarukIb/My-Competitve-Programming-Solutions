#include <bits/stdc++.h>
#define pii pair<int, int>
#define ll unsigned long long
#define ld long double

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    ll l, r;
    cin >> l >> r;

    bool hadOne = true;
    ll out = 0;
    for (int bit = 63; bit >= 0; bit--) {
        ll b = 1LL << bit;

        if ((l & b) != (r & b)) {
            out = b * 2 - 1;
            break;
        }
    }

    cout << out << "\n";
}
