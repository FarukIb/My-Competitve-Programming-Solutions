#include <bits/stdc++.h>
#define pii pair<int, int>
#define ll long long
#define ld long double

using namespace std;

int n, m, all = 0, k[(int)3e6];
pii ord[(int)3e6];
set<int> sale[(int)3e6];
 
bool valid(int d) {
    int tr = 0;
    for (int i = 0; i < n; i++)
    {
        if (sale[i].upper_bound(d) == sale[i].begin())
            ord[i] = {-1, i};
        else
            ord[i] = pii(*(--sale[i].upper_bound(d)), i);
    }
    sort(ord, ord + n);
    for (int i = 0; i < n; i++) {
        if (ord[i].first < 0)
            continue;
        int t = ord[i].second, amt=ord[i].first;
        tr += max(0, min(k[t], amt - tr));
    }
    return 2 * all - tr <= d;
}
 
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> n >> m;
    for (int i = 0; i < n; i++)
        cin >> k[i], all += k[i];
    for (int i=0, d, t; i<m; i++) {
        cin >> d >> t, t--;
        sale[t].insert(d);
    }
    
    int l=1, r = 2 * all;
    while (l < r) {
        int mid = (l + r) / 2;
        if (valid(mid))
            r = mid;
        else
            l = mid + 1;
    }
    cout << l << "\n";
}