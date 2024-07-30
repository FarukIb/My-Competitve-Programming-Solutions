#include <bits/stdc++.h>
#define mp make_pair
#define all(a) a.begin(), a.end()

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

const ll K = 20;

struct info {
    ll top, dist, min_cost;
    info() {}
    info(ll top, ll dist, ll min_cost) : top(top), dist(dist), min_cost(min_cost) {}
};

info merge(info head, info tail) {
    return info(head.top, head.dist + tail.dist, min(head.min_cost, tail.min_cost));
}

vector<ll> order;
vector<bool> visited;
void dfs(ll curr, vector<ll> &p, ll n) {
    if (curr == n || visited[curr])
        return;
    visited[curr] = true;
    dfs(p[curr], p, n);
    order.push_back(curr);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    ll n;
    cin >> n;
    vector<ll> p(n), d(n), c(n+1);
    for (int i = 1; i < n; i++)
        cin >> p[i] >> d[i] >> c[i];
    visited = vector<bool> (n + 1);
    
    vector<vector<info> > lift(K, vector<info>(n + 1));
    for (int i = 0; i < K; i++)
        lift[i][n] = info(n, 0, 0);
    for (int i = 1; i < n; i++)
        dfs(i, p, n);
    vector<ll> ans(n + 1, 0);
    for (ll guy : order) {
        lift[0][guy] = info(p[guy], d[guy], c[p[guy]]);
        for (int i = 1; i < K; i++)
            lift[i][guy] = merge(lift[i - 1][lift[i - 1][guy].top], lift[i - 1][guy]);
        
        info meeeeee(guy, 0, 1e9);
        for (int i = K - 1; i >= 0; i--) {
            if (lift[i][meeeeee.top].min_cost > c[guy])
                meeeeee = merge(lift[i][meeeeee.top], meeeeee);
        }
        meeeeee = merge(lift[0][meeeeee.top], meeeeee);

        ans[guy] = ans[meeeeee.top] + c[guy] * meeeeee.dist;
    }

    for (ll i = 1; i < n; i++)  
        cout << ans[i] << "\n";
}