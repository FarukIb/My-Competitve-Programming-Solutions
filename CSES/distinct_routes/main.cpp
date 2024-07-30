#include <bits/stdc++.h>
#define mp make_pair
#define all(a) a.begin(), a.end()

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

struct edge {
    int f, t, cap, flo;
    edge() {}
    edge(int f, int t, int cap) : f(f), cap(cap), t(t) {
        flo = 0;
    }
};

struct Dinitz {
    int n, s, t;
    vector<int> level, pnt;
    vector<vector<int> > graph;
    vector<edge> edges;

    Dinitz(int n, int s, int t) : n(n), s(s), t(t) {
        graph = vector<vector<int> > (n + 1);
    }

    void add_edge(int f, int t, int cap) {
        graph[f].push_back(edges.size());
        graph[t].push_back(edges.size() + 1);
        edges.emplace_back(f, t, cap);
        edges.emplace_back(t, f, 0);
    }

    bool bfs() {
        level = vector<int> (n + 1, -1);
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
            if (level[e.f] + 1 != level[e.t] || e.cap - e.flo < 1)
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

    void print_paths() {
        int num = get();
        cout << num << "\n";
        level = vector<int>(n + 1, -1);
        vector<vector<int> > paths(num);
        queue<pii> curr;
        for (int i = 0; i < num; i++)
            curr.push(pii(s, i));
        while (!curr.empty()) {
            pii me = curr.front(); curr.pop();
            paths[me.second].push_back(me.first);
            if (me.first == t)
                continue;
            for (int eid : graph[me.first]) {
                edge &e = edges[eid];
                if (e.flo <= 0)
                    continue;
                e.flo--;
                curr.push(pii(e.t, me.second));
                break;
            }
        }

        for (vector<int> path : paths) {
            cout << path.size() << "\n";
            for (int i : path)
                cout << i << " ";
            cout <<"\n";
        }
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int n, m;
    cin >> n >> m;
    Dinitz din(n, 1, n);
    for (int i = 0; i < m; i++) {
        int f, t;
        cin >> f >> t;
        din.add_edge(f, t, 1);
    }

    din.print_paths();
}