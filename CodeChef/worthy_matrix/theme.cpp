#include <bits/stdc++.h>
#define mp make_pair
#define all(a) a.begin(), a.end()
#define query(x1, y1, x2, y2) (mat[x2][y2] - (x1 != 0 ? mat[x1 - 1][y2] : 0) - (y1 != 0 ? mat[x2][y1 - 1] : 0) + (y1 != 0 and x1 != 0 ? mat[x1 - 1][y1 - 1] : 0))

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

int n, m;
vector<vector<ll> > mat;
void init() {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (j != 0)
                mat[i][j] += mat[i][j - 1];
            if (i != 0)
                mat[i][j] += mat[i - 1][j];
            if (i != 0 and j != 0)
                mat[i][j] -= mat[i - 1][j - 1];
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int t;
    cin >>t;
    while (t--) {
        ll k;
        cin >> n >> m >> k;
        mat = vector<vector<ll> > (n, vector<ll>(m));
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
                cin >> mat[i][j];
        init();

        ll num = 0;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                int max_siz = min(n - i - 1, m - j - 1);
                int l = 0, r = max_siz + 1;
                int ans = -1;
                while (l < r) {
                    int mid = (l + r) / 2;
                    ll val = query(i, j, i + mid, j + mid);
                    if (val >= k * (mid + 1) * (mid + 1))
                        r = mid;
                    else
                        l = mid + 1, ans = mid;
                }

                num += max_siz - ans;
            }
        }
        cout << num << "\n";
    }
}