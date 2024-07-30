#include <bits/stdc++.h>
#define pii pair<ll, ll>
#define ll long long
#define ld long double

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    ll n, m, p, k;
    cin >> n >> m >> k >> p;
    vector<vector<ll> > mat(n, vector<ll>(m));
    for (ll i = 0; i < n; i++) {
        for (ll j = 0; j < m; j++)
            cin >> mat[i][j];
    }

    vector<ll> row(n, 0);
    vector<ll> col(m, 0);
    for (ll i = 0; i < n; i++) 
        for (ll j = 0; j < m; j++)
            row[i] += mat[i][j], col[j] += mat[i][j];

    priority_queue<ll> rowq;
    priority_queue<ll> colq;
    for (ll i = 0; i < n; i++)
        rowq.push(row[i]);
    for (ll j = 0; j < m; j++)
        colq.push(col[j]);

    stack<ll> rowUpdates;
    ll sum = 0;
    for (ll i = 0; i < k; i++) {
        ll top = rowq.top(); rowq.pop();
        rowUpdates.push(top);
        sum += top;
        top -= p * m;
        rowq.push(top);
    }

    ll out = sum;
    for (ll i = k - 1; i >= 0; i--) {
        sum += colq.top();
        ll s = colq.top(); colq.pop();
        s -= p * n;
        colq.push(s);

        sum -= rowUpdates.top();
        rowUpdates.pop();

        out = max(out, sum - p * (k - i) * i);
    }

    cout << out << "\n";
}
