#include <bits/stdc++.h>
#define mp make_pair
#define all(a) a.begin(), a.end()

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int q;
    cin >> q;
    string out;
    for (int i = 1; i < 2000; i++)
        out += to_string(i);
    while (q--) {
        ll k;
        cin >> k;
        cout << out[k - 1] << "\n";
    }
}