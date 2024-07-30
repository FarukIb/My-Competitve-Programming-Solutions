#include <bits/stdc++.h>
#define mp make_pair
#define all(a) a.begin(), a.end()

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int n, m;
    cin >> n >> m;
    multiset<int> sett;
    for (int i = 0; i < n; i++) {
        int f;
        cin >>f;
        sett.insert(f);
    }
    for (int i = 0; i < m; i++) {
        int o;
        cin >>o;
        auto it = sett.upper_bound(o);
        if (it == sett.begin())
            cout << "-1\n";
        else {
            it--;
            cout << *it << "\n";
            sett.erase(it);
        }
    }
}