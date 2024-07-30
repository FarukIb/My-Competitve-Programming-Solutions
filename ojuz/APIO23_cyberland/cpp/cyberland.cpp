#include "cyberland.h"
#include <bits/stdc++.h>
#define all(a) a.begin(), a.end()

using namespace std;

const double INF = 1e18;

struct edge {
    double cost;
    int t;
    int inc;
    edge() {}
    edge(double cost, int t, bool inc) : cost(cost), t(t), inc(inc) { }
};

struct node {
    double cost;
    int idx, uses;
    node() {}
    node(double cost, int idx, int uses) : cost(cost), idx(idx), uses(uses) {

    }

    bool operator<(const node &b) const {
        return cost > b.cost;
    }
};

const int maxK = 80;

vector<vector<edge> > graph;
vector<int> type;
vector<double> pow2(maxK + 1);
int n, m, k, h;

vector<vector<double> > dijkstra() {
    int myk = min(k, maxK);
    vector<vector<double> > dist(n, vector<double>(myk + 1, INF));
    dist[h][0] = 0;
    priority_queue<node> q;
    q.push(node(0, h, 0));
    while (!q.empty()) {
        node me = q.top(); q.pop();
        if (dist[me.idx][me.uses] < me.cost || (me.idx == h and me.uses != 0))
            continue;
        for (auto &[cst, to, typ] : graph[me.idx]) {
            if (me.uses + typ > myk)
                continue;
            double new_cst = cst / pow2[me.uses] + me.cost;
            if (dist[to][me.uses + typ] > new_cst) {
                dist[to][me.uses + typ] = new_cst;
                q.push(node(new_cst, to, me.uses + typ));
            }
        }
    }
    return dist;
}

vector<bool> vis;
void dfs(int curr) {
    vis[curr] = true;
    if (curr == h)
        return;
    for (auto &[cst, to, typ] : graph[curr])
        if (!vis[to])
            dfs(to);
}

double solve(int N, int M, int K, int H, std::vector<int> x, std::vector<int> y, std::vector<int> c, std::vector<int> arr) {
    n = N, m = M, k = K, h = H;
    pow2[0] = 1;
    for (int i = 1; i <= maxK; i++)
        pow2[i] = pow2[i - 1] * 2.0;
    type = arr;
    vis = vector<bool> (n);
    graph = vector<vector<edge> > (n);
    for (int i = 0; i < m; i++) {
        graph[x[i]].push_back(edge(c[i], y[i], 0));
        graph[y[i]].push_back(edge(c[i], x[i], 0));
        if (type[y[i]] == 2)
            graph[x[i]].push_back(edge(c[i], y[i], 1));
        if (type[x[i]] == 2)
            graph[y[i]].push_back(edge(c[i], x[i], 1));
    }

    dfs(0);
    if (!vis[h])
        return -1;

    vector<vector<double> > dist = dijkstra();
    double out = *min_element(all(dist[0]));
    for (int i = 1; i < n; i++)
    {
        if (arr[i] == 0 and vis[i])
            out = min(out, *min_element(all(dist[i])));
    }

    return out;
}