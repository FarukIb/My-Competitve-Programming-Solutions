#include <bits/stdc++.h>
#define mp make_pair
#define all(a) a.begin(), a.end()

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int m, n;
    cin >> m >> n;
    set<int> towers;
    towers.insert(0);
    towers.insert(m);
    multiset<int> lengths;
    lengths.insert(0);
    lengths.insert(m);
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        auto it = prev(towers.lower_bound(x));
        auto itl = lengths.find(*next(it) - *it);
        int l1 = x - *it, l2 = *next(it) - x;
        lengths.erase(itl);
        lengths.insert(l1);
        lengths.insert(l2);
        towers.insert(x);
        cout << *prev(lengths.end()) << "\n";
    }
}