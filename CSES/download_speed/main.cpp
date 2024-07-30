#include <bits/stdc++.h>
#define mp make_pair
#define all(a) a.begin(), a.end()

using namespace std;

typedef long long ll;
typedef pair<ll, ll> pii;

struct edge {
    ll f, t;
    ll cap, flow;
    edge(ll F, ll T, ll CAP) {
        f = F, t = T, cap = CAP, flow = 0;
    }
    edge() {flow = 0;}
};

struct Dinitz {
    vector<edge> edges;
    vector<vector<ll> > graph;
    vector<ll> level, pnt;
    ll s, t, n;

    Dinitz(ll N, ll S, ll T) {
        graph = vector<vector<ll> > (N  + 1);
        level = pnt = vector<ll> (N + 1);
        s = S, t = T, n = N;
    }

    void add_edge(ll f, ll t, ll cap) {
        edges.push_back(edge(f, t, cap));
        edges.push_back(edge(t, f, 0));
        graph[f].push_back(edges.size() - 2);
        graph[t].push_back(edges.size() - 1);
    }

    bool bfs() {
        fill(all(level), -1);
        level[s] = 0;
        queue<ll> q; q.push(s);
        while (!q.empty()) {
            ll c = q.front(); q.pop();
            for (ll id : graph[c]) {
                edge e = edges[id];
                if (level[e.t] != -1 || e.cap - e.flow < 1)
                    continue;
                level[e.t] = level[e.f] + 1;
                q.push(e.t);
            }
        }
        return level[t] != -1;
    }

    ll push_flow(ll curr, ll pushed) {
        if (curr == t)
            return pushed;
        for (ll &cid = pnt[curr]; cid < graph[curr].size(); cid++) {
            ll id = graph[curr][cid];
            edge e = edges[id];
            if (level[e.t] != level[curr] + 1 || e.cap - e.flow < 1)
                continue;
            ll flo = push_flow(e.t, min(e.cap - e.flow, pushed));
            if (flo == 0)
                continue;
            edges[id].flow += flo;
            edges[id^1].flow -= flo;
            return flo;
        }
        return 0;
    } 

    ll compute() {
        ll tot = 0;
        while (bfs()) {
            pnt = vector<ll> (n + 1);
            while (1) {
                ll val = push_flow(s, 1e18);
                if (val == 0)
                    break;
                tot += val;
            }

        }
        return tot;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    ll n, m;
    cin >> n >> m;
    Dinitz din(n, 1, n);
    for (int i = 0; i < m; i++) {
        int f, t, c;
        cin >> f >> t >> c;
        din.add_edge(f, t, c);
    }

    cout << din.compute() << endl;
}