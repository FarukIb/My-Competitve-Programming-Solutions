#include <bits/stdc++.h>
#define pii pair<int, int>
#define ll long long
#define ld long double

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int n, m, q;
    cin >> n >> m >> q;
    vector<vector<vector<bool> > > pers(q + 1, vector<vector<bool> >(n, vector<bool>(m, false)));
    vector<int> pers2(q + 1, 0);

    vector<vector<bool> > curr(n, vector<bool>(m, false));
    int sum = 0;

    for (int Q = 1; Q <= q; Q++) {
        int type;
        cin >> type;
        if (type == 1) {
            int i, j;
            cin >> i >> j;
            i--, j--;
            if (!curr[i][j])
                sum++, curr[i][j] = true;
            pers[Q] = curr;
            pers2[Q] = sum;
            cout << sum << "\n";
        }
        else if (type == 2) {
            int i, j;
            i--, j--;
            cin >> i >> j;
            if (curr[i][j])
                sum--, curr[i][j] = false;
            pers[Q] = curr;
            pers2[Q] = sum;
            cout << sum << "\n";
        }
        else if (type == 3) {
            int j;
            cin >> j;

            for (int i = 0; i < n; i++)
            {
                if (curr[i][j])
                    sum--, curr[i][j] = false;
                else
                    sum++, curr[i][j] = true;
            }

            pers[Q] = curr;
            pers2[Q] = sum;
            cout << sum << "\n";
        }
        else {
            int k;
            cin >> k;

            curr = pers[k];
            sum = pers2[k];

            pers[Q] = curr;
            pers2[Q] = sum;
            cout << sum << "\n";
        }
    }
}
