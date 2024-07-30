#include <bits/stdc++.h>
#define pii pair<int, int>
#define ll long long
#define ld long double

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int n;
    cin >> n;
    vector<vector<ll> > a(n, vector<ll>(n, 0));
    vector<vector<ll> > b(n, vector<ll>(n, 0));

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            cin >> a[i][j];
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            cin >> b[i][j];

    ll prod = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < n; k++)
                prod += a[i][k] * b[k][j];
        }
    }

    int Q;
    cin >> Q;
    while (Q--) {
        char typ;
        cin >> typ;
        if (typ == 'A') {
            int x, y; ll K;
            cin >> x >> y >> K;

            for (int k = 0; k < n; k++)
                prod -= a[x][y] * b[k][y], prod += K * b[k][y];
            a[x][y] = K;
        }
        else {
            int x, y; ll K;
            cin >> x >> y >> K;

            for (int k = 0; k < n; k++)
                prod -= b[x][y] * a[k][y], prod += K * a[k][y];
            b[x][y] = K;
        }
        cout << prod << "\n";
    }
}
