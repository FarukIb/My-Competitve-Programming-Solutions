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
    vector<int> mini(n+1, 2e9); mini[0] = 0; int out = 0;
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        auto it = lower_bound(all(mini), x);
        *it = min(*it, x);
        out = max(out, (int)(it - mini.begin()));
    }

    cout << out << endl;
}