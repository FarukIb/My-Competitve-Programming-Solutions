#include <bits/stdc++.h>
#define mp make_pair
#define all(a) a.begin(), a.end()

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

struct edge {
    int f, t, cap, flo;
    edge() {flo = 0;}
    edge(int f, int t, int cap) : f(f), t(t), cap(cap) {
        flo = 0;
    }
};

struct Dinitz {
    int n, s, t;
    vector<edge> edges;
    vector<int> level, pnt;
    vector<vector<int> > graph;

    Dinitz() {}
    Dinitz(int n, int s, int t) : n(n), s(s), t(t) {
        graph = vector<vector<int> > (n + 1);
        level = pnt = vector<int> (n + 1, - 1);
    }

    void add_edge(int f, int t, int cap) {
        graph[f].push_back(edges.size());
        graph[t].push_back(edges.size() + 1);
        edges.emplace_back(f, t, cap);
        edges.emplace_back(t, f, 0);
    }

    bool bfs() {
        fill(all(level), -1);
        level[s] = 0;
        queue<int> q; q.push(s);
        while (!q.empty()) {
            int curr = q.front(); q.pop();
            for (int eid : graph[curr]) {
                edge e = edges[eid];
                if (level[e.t] != -1 || e.cap - e.flo < 1)
                    continue;
                level[e.t] = level[e.f] + 1;
                q.push(e.t);
            }
        }
        return level[t] != -1;
    }

    int push_flow(int curr, int pushed) {
        if (curr == t)
            return pushed;
        for (int &i = pnt[curr]; i < graph[curr].size(); i++) {
            int eid = graph[curr][i];
            edge e = edges[eid];
            if (level[e.t] != level[e.f] + 1 || e.cap - e.flo < 1)
                continue;
            int flo = push_flow(e.t, min(pushed, e.cap - e.flo));
            if (flo == 0)
                continue;
            edges[eid].flo += flo;
            edges[eid^1].flo -= flo;
            return flo;
        }
        return 0;
    }

    int get() {
        int tot = 0;
        while (bfs()) {
            fill(all(pnt), 0);
            while (1) {
                int curr = push_flow(s, 1e9);
                if (curr == 0)
                    break;
                tot += curr;
            }
        }
        return tot;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int n, m, k;
    cin >> n >> m >> k;
    Dinitz din(n + m + 1, 0, n + m + 1);
    for (int i = 1; i <= n; i++)
        din.add_edge(din.s, i, 1);
    for (int i = n + 1; i <= n + m; i++)
        din.add_edge(i, din.t, 1);
    for (int i = 0; i < k; i++) {
        int f, t;
        cin >> f >> t;
        f++, t++;
        din.add_edge(f, t + n, 1);
    }
    cout << din.get() << "\n";
    for (edge e : din.edges) {
        if (e.f == din.s || e.t == din.t)
            continue;
        if (e.flo == 1)
            cout << e.f - 1 << " " << e.t - n - 1 << "\n";
    }
}