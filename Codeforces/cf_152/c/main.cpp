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
    cin >> t;
    while (t--) {
        int n, m;
        cin >> n >> m;
        string s;
        cin >> s;
        set<pii> zeros;
        set<pii> ones;
        int last = 0;
        for (int i = 1; i < n; i++) {
            if (s[i] != s[i - 1])
            {
                if (s[i - 1] == '0')
                    zeros.insert({last, i - 1});
                else
                    ones.insert({last, i - 1});
                last = i;
            }
        }
        if (s[n - 1] == '0')
            zeros.insert({last, n - 1});
        else
            ones.insert({last, n - 1});
        
        set<pii> sett;
        for (int i = 0; i < m; i++) {
            int l, r;
            cin >> l >> r;
            l--, r--;
            auto rint = ones.lower_bound({r, 1e9});
            if (rint != ones.begin()) {
                rint = prev(rint);
                if (rint->first <= r and rint->second >= r)
                    r = rint->first - 1;
            }
            auto lint = zeros.lower_bound({l, 1e9});
            if (lint != zeros.begin()) {
                lint = prev(lint);
                if (lint->first <= l and lint->second >= l)
                    l = lint->second + 1;
            }
            
            if (l >= r)
                sett.insert(mp(0, 0));
            else
                sett.insert(mp(l, r));
        }
        cout << sett.size() << "\n";
    }
}