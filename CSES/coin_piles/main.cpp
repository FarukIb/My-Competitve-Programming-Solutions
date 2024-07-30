#include <bits/stdc++.h>
#define mp make_pair
#define all(a) a.begin(), a.end()

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int t;
    cin >>t;
    while (t--) {
        ll a, b;
        cin >> a >> b;
        if (a < b)
            swap(a, b);
        if ((a + b) % 3 != 0) {
            cout << "NO" << endl;
            continue;
        }
        if (a - b >= 1) {
            ll x = a - b;

            a -= x * 2, b -= x;

            if (a < 0 || b < 0) {
                cout << "NO" <<endl;
                continue;
            }
        }
        cout << "YES" << endl;
    }
}