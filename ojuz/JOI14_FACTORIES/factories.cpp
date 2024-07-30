#include <bits/stdc++.h>
#include "factories.h"
#define mp make_pair
#define all(a) a.begin(), a.end()

using namespace std;

typedef long long ll;
typedef pair<ll, ll> pii;

const int K = 20;
struct rmq {
    int n;
    vector<int> lg;
    vector<vector<pii> > table;

    rmq() {}
    rmq(vector<pii> arr) {
        n = arr.size();
        lg.resize(n + 1);
        for (int i = 2; i <= n; i++)
            lg[i] = lg[i / 2] + 1;
        table.resize(K, vector<pii>(n));
        table[0] = arr;
        for (int i = 1; i < K; i++)
            for (int j = 0; j + (1 << i) <= n; j++)
                table[i][j] = min(table[i - 1][j], table[i - 1][j + (1 << (i - 1))]);    
    }

    pii query(int l, int r) {
        int siz = lg[r - l + 1];
        return min(table[siz][l], table[siz][r - (1 << siz) + 1]);
    }
};

int n;
vector<vector<pii> > graph;
vector<int> beg;
vector<int> endd;
vector<pii> euler_tour;
vector<ll> dist_to_1;
rmq lca_rmq;
void dfs_lca(int curr, int par, ll height, ll dt1) {
    beg[curr] = euler_tour.size();
    dist_to_1[curr] = dt1;
    euler_tour.push_back({height, curr});

    for (pii a : graph[curr]) {
        if (a.first == par)
            continue;
        dfs_lca(a.first, curr, height + 1, dt1 + a.second);
        euler_tour.push_back({height, curr});
    }
    endd[curr] = euler_tour.size() - 1;
}

void init_lca() {
    beg = vector<int>(n + 1);
    endd = vector<int>(n + 1);
    dist_to_1 = vector<ll>(n + 1);
    dfs_lca(0, -1, 0, 0);
    lca_rmq = rmq(euler_tour);
}

int lca(int a, int b) {
    if (beg[a] > beg[b])
        swap(a, b);
    return lca_rmq.query(beg[a], endd[b]).second;
}

ll dist(int a, int b) {
    if (a == b)
        return 0;
    return dist_to_1[a] + dist_to_1[b] - 2LL*dist_to_1[lca(a, b)];
}

// centroid init
vector<int> centroid_par;
vector<bool> vis;
vector<int> sz;

int get_siz(int curr, int par) {
    sz[curr] = 1;
    for (auto &[a, d] : graph[curr]) 
        if (!vis[a] and a != par)
            sz[curr] += get_siz(a, curr);
    return sz[curr];
}

int get_centroid(int curr, int par, int subtree_size) {
    for (auto &[a, d] : graph[curr])
        if (!vis[a] and a != par and 2LL * sz[a] > subtree_size)
            return get_centroid(a, curr, subtree_size);
    return curr;
}

void centroid_init(int curr, int c_par) {
    int my_siz = get_siz(curr, -1);
    int centroid = get_centroid(curr, -1, my_siz);
    vis[centroid] = 1;
    centroid_par[centroid] = c_par;
    for (auto &[a, d] : graph[centroid])
        if (!vis[a])
            centroid_init(a, centroid);
}

void centroid_full_init() {
    centroid_par = vector<int>(n+1);
    vis = vector<bool>(n+1);
    sz = vector<int>(n+1);
    centroid_init(0, -1);
}

vector<ll> best;
void Init(int N, int A[], int B[], int D[]) {
    n = N;
    graph = vector<vector<pii> >(N+1);
    for (int i = 0; i < n - 1; i++)
    {
        graph[A[i]].push_back({B[i], D[i]});
        graph[B[i]].push_back({A[i], D[i]});
    }
    init_lca();
    centroid_full_init();
    best = vector<ll>(n+1,1e18);
}

vector<int> changed;
void change_col(int curr, int og) {
    if (curr == -1)
        return;
    if (best[curr] > dist(curr, og))
        changed.push_back(curr);
    best[curr] = min(best[curr], dist(curr, og));
    change_col(centroid_par[curr], og);
}

ll query(int curr, int og) {
    if (curr == -1)
        return 1e18;
    return min(best[curr] + dist(curr, og), query(centroid_par[curr], og));
}

long long Query(int S, int X[], int T, int Y[]) {
    for (int i = 0; i < S; i++)
        change_col(X[i], X[i]);
    ll out = 1e18;
    for (int i = 0; i < T; i++)
        out = min(out, query(Y[i], Y[i]));
    for (int a : changed)
        best[a] = 1e18;
    changed.clear();
    return out;
}