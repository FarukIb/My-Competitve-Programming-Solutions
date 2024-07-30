#include <bits/stdc++.h>
#define pii pair<int, int>
#define ll long long
#define ld long double

using namespace std;

struct edge {
    int f, t;
    int w;

    bool operator<(const edge& b) const { return w < b.w; }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int n;
    int m;
    cin >> n >> m;
    vector<edge> edges(m);
    for (int i = 0; i < m; i++)
        cin >> edges[i].f >> edges[i].t >> edges[i].w;

    sort(edges.begin(), edges.end());

    vector<int> dp(n + 1, 0);
    set<pii> changes;
    changes.insert(pii(edges[0].t, 1));
    for (int i = 1; i < m; i++) {
        if (edges[i].w != edges[i - 1].w) {
            for (pii x : changes)
                dp[x.first] = max(dp[x.first], x.second);
            changes.clear();
        }
        edge x = edges[i];
        if (dp[x.t] < dp[x.f] + 1)
            changes.insert(pii(x.t, dp[x.f] + 1));
    }
    for (pii x : changes)
        dp[x.first] = max(dp[x.first], x.second);
    
    int out = 0;
    for (int i = 1; i <= n ; i++)
    {
        out = max(out, dp[i]);
    }

    cout << out << "\n";
}
