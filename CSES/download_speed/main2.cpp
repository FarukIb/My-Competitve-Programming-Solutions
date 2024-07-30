#include <bits/stdc++.h>
#define mp make_pair
#define all(a) a.begin(), a.end()

using namespace std;

typedef long long ll;
typedef pair<ll, ll> pii;

const ll INF = 1e18;

struct edge {
    ll cap, f, t, flow;
    edge() {}
    edge(ll cap, ll f, ll t) : cap(cap), f(f), t(t) {
        flow = 0;
    }
};

struct Dinitz {
    vector<ll> dep, pnt;
    vector<vector<ll> > graph;
    vector<edge> edges;
    ll s, t, n;
    
    Dinitz() {

    }

    Dinitz(ll num_nodes, ll s, ll t) : s(s), t(t) {
        n = num_nodes;
        dep = pnt = vector<ll> (n + 1);
        graph = vector<vector<ll> > (n + 1);
    }

    void add_edge(ll f, ll t, ll cap) {
        edges.emplace_back(cap, f, t);
        edges.emplace_back(0, t, f);
        graph[f].push_back(edges.size() - 2);
        graph[t].push_back(edges.size() - 1);
    }

    void bfs() {
        fill(all(dep), INF);
        dep[s] = 0;
        queue<ll> q;
        q.push(s);
        while (!q.empty()) {
            ll curr = q.front(); q.pop();
            for (ll e_id : graph[curr]) {
                edge &e = edges[e_id];
                if (dep[e.t] != INF || e.cap - e.flow < 1)
                    continue;
                dep[e.t] = dep[e.f] + 1;
                q.push(e.t);
            }
        }
    }

    ll push_flow(ll curr, ll flow) {
        if (curr == t)
            return flow;
        for (ll &id1 = pnt[curr]; id1 < graph[curr].size(); id1++) {
            ll eid = graph[curr][id1];
            edge &e = edges[eid];
            if (e.cap - e.flow < 1 || dep[e.t] != dep[e.f] + 1)
                continue;
            ll flo = push_flow(e.t, min(flow, e.cap - e.flow));
            if (flo == 0)
                continue;
            edges[eid].flow += flo;
            edges[eid^1].flow -= flo;
            return flo;
        }
        return 0;
    }

    ll get_flow() {
        ll flo = 0;
        while (1) {
            bfs();
            if (dep[t] == INF)
                break;
            fill(all(pnt), 0);
            while (1) {
                ll c = push_flow(s, INF);
                if (c == 0)
                    break;
                flo += c;
            }
        }
        return flo;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int n, m;
    cin >> n >> m;
    Dinitz din(n, 1, n);
    for (int i = 0; i < m; i++) {
        int f, t, flo;
        cin >> f >> t >> flo;
        din.add_edge(f, t, flo);
    }

    cout << din.get_flow() << "\n";
}