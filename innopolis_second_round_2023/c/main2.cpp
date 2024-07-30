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
    int offs = n+m;
    vector<vector<int> > mat(n, vector<int>(m));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> mat[i][j];
        }
    }

    ll out = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            for (int a = 1; i + a < n; a++) {
                for (int b = 1; b + j < m; b++) {
                    int F = mat[i][j], B = mat[i + a][j], A = mat[i][j + b];

                    int need = b - B;
                    F += need, B += need, A += need;
                    if (F == b + a and A == a)
                        out++;
                }
            }
        }
    }

    cout << out << endl;
}