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
    vector<vector<int> > mat(n, vector<int>(m));
    vector<map<int, vector<int> > > idxs(n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> mat[i][j];
            idxs[i][mat[i][j] - (m - 1 - j)].push_back(j);
        }
    }

    ll out = 0;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            for (int k = j + 1; k < n; k++)    {
                int a = k - j, b = mat[k][i];
                if (mat[j][i] != a + mat[k][i])
                    continue;
                int val = a - (m - 1 - (i + b));
                int idx1 = lower_bound(all(idxs[j][val]), i + 1) - idxs[j][val].begin();
                out += idxs[j][val].size() - idx1;
            }
        }
    }

    cout << out << "\n";
}