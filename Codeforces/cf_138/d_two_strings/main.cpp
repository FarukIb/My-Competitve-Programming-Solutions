#include <bits/stdc++.h>
#define pii pair<int, int>
#define ll long long
#define ld long double

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    vector<int> mini(30, (int)1e9);
    vector<int> maxi(30, (int)-1e9);

    string s, t;
    cin >> s >> t;
    int n = s.size(), m = t.size();

    int pnt = 0;
    for (int i = 0; i < n && pnt < m; i++) {
        if (t[pnt] == s[i])
        {
            mini[t[pnt] - 'a'] = min(mini[t[pnt] - 'a'], i);
            maxi[t[pnt] - 'a'] = max(maxi[t[pnt] - 'a'], i);
            pnt++;
        }
    }
    if (pnt < m) {
        cout << "No\n";
        return 0;
    }

    pnt = m - 1;
    for (int i = n - 1; i >= 0 && pnt >= 0; i--) {
        if (t[pnt] == s[i]) {
            maxi[t[pnt] - 'a'] = max(maxi[t[pnt] - 'a'], i);
            mini[t[pnt] - 'a'] = min(mini[t[pnt] - 'a'], i);
            pnt--;
        }
    }
    if (pnt >= 0) {
        cout << "No\n";
        return 0;
    } 

    bool good = true;
    for (int i = 0; i < n; i++) {
        if (i >= mini[s[i] - 'a'] && i <= maxi[s[i] - 'a'])
            continue;
        good = false;
    }

    if (good)
        cout << "Yes\n";
    else
        cout << "No\n";
}
