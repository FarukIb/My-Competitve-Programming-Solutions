#include <bits/stdc++.h>
#define mp make_pair

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int n, m;
    cin >> n >>m;

    vector<vector<pii> > hor(n + 1);
    vector<vector<pii> > diag1(2 * n + 1);
    vector<vector<pii> > diag2(2* n + 1);
    vector<vector<pii> > vert(n + 1);

    for (int i = 0; i < m; i++) {
        int r, c;
        cin >> r >> c;

        hor[r].push_back(pii(c, i));
        vert[c].push_back(pii(r, i));

        diag1[r + c].push_back(pii(r, i));
        diag2[r - c + n].push_back(pii(r, i));
    }

    vector<int> num(m, 0);
    for (vector<pii> x : hor) {
        vector<pii> s = x;
        sort(s.begin(), s.end());
        if (s.size() <= 1)
            continue;
        num[s[0].second]++;
        num[s[s.size() - 1].second]++;
        for (int i = 1; i < s.size() - 1; i++)
            num[s[i].second] += 2;
    }
    for (vector<pii> x : vert) {
        vector<pii> s = x;
        sort(s.begin(), s.end());
        if (s.size() <= 1)
            continue;
        num[s[0].second]++;
        num[s[s.size() - 1].second]++;
        for (int i = 1; i < s.size() - 1; i++)
            num[s[i].second] += 2;
    }
    for (vector<pii> x : diag1) {
        vector<pii> s = x;
        sort(s.begin(), s.end());
        if (s.size() <= 1)
            continue;
        num[s[0].second]++;
        num[s[s.size() - 1].second]++;
        for (int i = 1; i < s.size() - 1; i++)
            num[s[i].second] += 2;
    }
    for (vector<pii> x : diag2) {
        vector<pii> s = x;
        sort(s.begin(), s.end());
        if (s.size() <= 1)
            continue;
        num[s[0].second]++;
        num[s[s.size() - 1].second]++;
        for (int i = 1; i < s.size() - 1; i++)
            num[s[i].second] += 2;
    }

    vector<int> out(10, 0);
    for (int i = 0; i < m; i++)
        out[num[i]]++;
    
    for (int i = 0; i < 9; i++)
        cout << out[i] << " ";
    cout << "\n";

    return 0;
}