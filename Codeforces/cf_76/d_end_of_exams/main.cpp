#include <bits/stdc++.h>
#define ld long double
#define pii pair<int, int>

using namespace std;

int main() {
    int n, w, m;
    cin >> n >> w >> m;

    w *= m;
    int limit = n * w / m;

    vector<vector<pii> > cup(m);
    vector<int> cap(m, 0);

    int curr = 1, left = w;
    int cCup = 0;

    while (curr <= n) {
        if (limit - cap[cCup] < left)
        {
            cup[cCup].push_back(pii(curr, limit - cap[cCup]));
            left -= limit - cap[cCup], cap[cCup] = limit, cCup++;
        }
        else if (limit - cap[cCup] == left)
        {
            cup[cCup].push_back(pii(curr, limit - cap[cCup]));
            cap[cCup] = limit, left = w, curr++, cCup++;
        }
        else if (limit - cap[cCup] > left)
        {
            cup[cCup].push_back(pii(curr, left));
            cap[cCup] += left;

            left = w, curr++;
        }
    }

    vector<int> occ(n + 1, 0);
    for (vector<pii> x : cup) {
        for (pii i : x)
            occ[i.first]++;
    }

    for (int i = 1; i <= n; i++) {
        if (occ[i] > 2)
        {
            cout << "NO" << "\n";
            return 0;
        }
    }

    cout << "YES" << "\n";
    for (vector<pii> x : cup) {
        for (pii i : x)
            cout << i.first << " " << fixed << setprecision(9) << (ld)i.second / (ld) m << " ";
        cout << "\n";
    }
}