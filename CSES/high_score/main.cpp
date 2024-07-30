#include <bits/stdc++.h>
#define mp make_pair
#define all(a) a.begin(), a.end()

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

struct edge {
    ll f,t,w;
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int n, m;
    cin >> n >> m;
    vector<edge> edges(m);
    vector<vector<int> > adj(n + 1);
    vector<vector<int> > adj2(n + 1);
    for (int i = 0; i < m; i++) {
        edge e;
        cin >> e.f >> e.t >> e.w;
        edges[i] = e;
        adj[e.t].push_back(e.f);
        adj2[e.f].push_back(e.t);
    }
    vector<ll> maxi(n + 1, -1e18);
    maxi[1] = 0; 
    vector<bool> updated(n+1, false);
    for (int i = 0; i < n; i++) {
        int o = -1;
        for (edge e : edges) {
            if (maxi[e.t] < maxi[e.f] + e.w)
                o = max(o, (int)e.t), maxi[e.t] = maxi[e.f] + e.w, updated[e.t] = i == n - 1 ? true : false;
        }
        if (o == -1)
            break;
    }

    vector<bool> visited(n + 1);
    function<void(int, vector<vector<int> >&, vector<bool>&)> dfs;

    dfs = [&](int curr, vector<vector<int> > &adj, vector<bool> &visited) {
        visited[curr] = true;
        for (int a : adj[curr])
            if (!visited[a])
                dfs(a, adj, visited);
    };
    dfs(n, adj, visited);
    vector<bool> visited2(n+1);
    dfs(1, adj2, visited2);

    bool bad = false;
    for (int i = 1; i <= n; i++)
        if (visited[i] and visited2[i] and updated[i])
            bad = true;

    if (!bad)
        cout << maxi[n] << "\n";
    else
        cout << "-1\n";
}