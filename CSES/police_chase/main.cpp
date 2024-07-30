#include <bits/stdc++.h>
#define mp make_pair
#define all(a) a.begin(), a.end()

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

struct edge {
    int f, t, cap, flow;
    edge() {}
    edge(int f, int t, int cap) : f(f), t(t), cap(cap) {
        flow = 0;
    }
};

struct Dinitz {
    int n, s, t;
    vector<int> level, pnt;
    vector<edge> edges;
    vector<vector<int> > graph;

    Dinitz() {}
    Dinitz(int n, int s, int t) : n(n), s(s), t(t) {
        level = pnt = vector<int> (n + 1);
        graph = vector<vector<int> > (n + 1);
    }

    void add_edge(int f, int t, int cap) {
        graph[f].push_back(edges.size());
        graph[t].push_back(edges.size() + 1);
        edges.emplace_back(f, t, cap);
        edges.emplace_back(t, f, 0);
    }

    bool bfs() {
        level = vector<int>(n + 1, -1);
        queue<int> q; q.push(s);
        level[s] = 0;
        while (!q.empty()) {
            int curr = q.front(); q.pop();
            for (int eid : graph[curr]) {
                edge e = edges[eid];
                if (level[e.t] != -1 || e.cap - e.flow < 1)
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
            int id = graph[curr][i];
            edge e = edges[id];
            if (level[e.f] + 1 != level[e.t] || e.cap - e.flow < 1)
                continue;
            int flow = push_flow(e.t, min(pushed, e.cap - e.flow));
            if (flow == 0)
                continue;
            edges[id].flow += flow;
            edges[id^1].flow += flow;
            return flow;
        }
        return 0;
    }

    int get() {
        int tot = 0;
        while (bfs()) {
            pnt = vector<int> (n + 1);
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

    int n, m;
    cin >> n >> m;
    Dinitz din(n, 1, n);
    vector<vector<bool> > edges(n + 1, vector<bool>(n + 1));
    for (int i = 0; i < m; i++) {
        int f, t;
        cin >> f >> t;
        din.add_edge(f, t, 1);
        din.add_edge(t, f, 1);
        edges[f][t] = true;
    }

    int num = din.get();
    cout << num << "\n";
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if ((din.level[i] == -1 || din.level[j] == -1) and din.level[i] != din.level[j] and edges[i][j])
                cout << i << " " << j << "\n";
        }
    }
}