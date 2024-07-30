#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

struct edge {
    ll loss, gain, idx;
    edge() {}
    edge(ll L, ll G, ll I) {
        loss = L, gain = G, idx = I;
    }

    bool operator<(const edge& b) const {
        return loss < b.loss;
    }
};

vector<ll> to, op;
vector<vector<edge> > gain_graph;
vector<vector<ll> > graph;
vector<ll> cst;
vector<bool> in_cyc, vis;

void dfs(ll me, ll cnst) {
    if (to[me] == 0) {
        in_cyc[me] = false;
        vis[me] = true;
        return;
    }
    if (vis[me])
    {
        if (op[me] == cnst) {
            ll c = to[me];
            in_cyc[me] = true;
            while (c != me) {
                in_cyc[c] = true;
                c = to[c];
            }
        }
        return;
    }
    vis[me] = true;
    op[me] = cnst;
    dfs(to[me], cnst);
}

void dfs2(ll curr, ll lst, ll mini, ll sum) {
    if (in_cyc[curr])
        return;
    sum += cst[curr];
    mini = min(mini, sum);

    if (sum > 0) {
        gain_graph[lst].push_back(edge(mini, sum, curr));
        for (ll i : graph[curr])
            dfs2(i, curr, 0, 0);
         
    } else {
        for (ll i : graph[curr])
            dfs2(i, lst, mini, sum);
    }
}

int main() {
    ios_base::sync_with_stdio(false);

    ll n, s;
    cin >> n >>s;
    
    to = op = vector<ll>(n + 1);
    cst = vector<ll> (n + 1);
    in_cyc = vis = vector<bool>(n + 1);
    graph = vector<vector<ll> > (n + 1);
    gain_graph = vector<vector<edge> > (n + 1);
    for (ll i = 1; i <= n; i++)
    {
        cin >> cst[i] >> to[i];
        graph[to[i]].push_back(i);
    }
    
    for (ll i = 1; i <= n; i++)
        if (!vis[i])
            dfs(i, i);
    for (ll i : graph[0])
        dfs2(i, 0, 0, 0);

    // idx, min
    priority_queue<edge> q;
    for (edge e : gain_graph[0])
        q.push(e);
    ll csum = s;
    while (!q.empty()) {
        edge curr = q.top(); q.pop();
        if (csum + curr.loss < 0)
            break;
        csum += curr.gain;
        for (edge e : gain_graph[curr.idx])
            q.push(e);
    }

    cout << csum - s << "\n";
}