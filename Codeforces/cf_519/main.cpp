#include <bits/stdc++.h>
#define pii pair<int, int>
#define ll long long
#define ld long double

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int n, m;
    cin >> n >> m;

    vector<vector<int> > arrs(m, vector<int>(n + 1));
    vector<vector<int> > pnt(m, vector<int>(n + 1));
    for (int i =0 ; i < m; i++) {
        for (int j = 0; j < n; j++)
        {
            cin >> arrs[i][j];
            pnt[i][arrs[i][j]] = j;
        }
        arrs[i][n] = -i;
     }

    ll out = 0;
    for (int i = 0; i < n; i++) {
        vector<int> curr(m);
        int first = arrs[0][i];
        for (int j = 0; j < m; j++)
            curr[j] = pnt[j][first];
        
        int OG = i, len = 1;
        for (; len < n && i < n; len++, i++) {
            bool broke = false;
            for (int j = 1; j < m; j++) {
                int curr = arrs[0][i + 1];
                if (arrs[j][pnt[j][first] + len] != curr) {
                    broke = true;
                    break;
                }
            }
            if (broke)
                break;
        }

        out += (ll)len * ((ll)len + 1) / 2;
    }

    cout << out << "\n";
}
