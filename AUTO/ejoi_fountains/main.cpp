#include <bits/stdc++.h>
#define mp make_pair
#define all(a) a.begin(), a.end()
#define cap first
#define idx second

using namespace std;

typedef long long ll;
typedef pair<ll, ll> pii;

const int K = 20;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int n, q;
    cin >> n >>q;
    vector<pii> font(n);
    for (int i = 0; i < n; i++) 
        cin >> font[i].first >> font[i].second; // second is capacity

    vector<vector<pii> > lft(K, vector<pii>(n+1));
    for (int i = 0; i < K; i++)
        lft[i][n].idx = n, lft[i][n].cap = 0;
    stack<pii> stck;
    stck.push({2e9, n});
    for (int i = n - 1; i >= 0; i--) {
        while (stck.top().first <= font[i].first)
            stck.pop();
        lft[0][i].cap = font[i].second;
        lft[0][i].idx = stck.top().second;
        for (int k = 1; k < K; k++)
            lft[k][i].idx = lft[k - 1][lft[k - 1][i].idx].idx, lft[k][i].cap = lft[k - 1][i].cap + lft[k - 1][lft[k - 1][i].idx].cap;
        stck.push(mp(font[i].first, i));
    }

    while (q--) {
        ll id, val;
        cin >> id >> val;
        id--;
        for (int k = K - 1; k >= 0; k--) 
        {
            if (val > lft[k][id].cap)
                val -= lft[k][id].cap, id = lft[k][id].idx;
        }
        if (id == n)
            id = -1;
        cout << id + 1 << "\n";
    }
}