#include <bits/stdc++.h>
#define mp make_pair
#define all(a) a.begin(), a.end()

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

const int K = 20;

// LCA
struct rmq {
    int siz;
    vector<vector<pii> > table;
    vector<int> lg;
    rmq() {}
    rmq(vector<pii> arr) {
        siz = arr.size();
        lg.resize(siz + 1);
        for (int i = 2; i <= siz; i++)
            lg[i] = lg[i / 2] + 1;

        table = vector<vector<pii> > (K, vector<pii>(siz));
        table[0] = arr;
        for (int i = 1; i < K; i++) {
            for (int j = 0; j + (1 << i) <= siz; j++)
                table[i][j] = min(table[i - 1][j], table[i - 1][j + (1 << i - 1)]);
        }
    }

    pii query(int l, int r) {
        int s = lg[r - l + 1];
        return min(table[s][l], table[s][r - (1 << s) + 1]);
    }
};

int n;
vector<vector<int> > graph;
vector<pii> euler_tour;
rmq lca_rmq;
vector<int> height;
vector<int> beg;
vector<int> endd;
void get_tour(int curr, int par, int height) {
    beg[curr] = euler_tour.size();
    euler_tour.push_back({height, curr});
    for (int a : graph[curr]) {
        if (a == par)
            continue;
        get_tour(a, curr, height + 1);
        euler_tour.push_back({height, curr});
    }
    endd[curr] = euler_tour.size() - 1;
}

void init_lca() {
    beg.resize(n + 1);
    endd.resize(n + 1);
    get_tour(1, 0, 0);
    lca_rmq = rmq(euler_tour);
}

int lca(int a, int b) {
    if (beg[a] > beg[b])
        swap(a, b);
    return lca_rmq.query(beg[a], endd[b]).second;
}

int distance(int a, int b) {
    if (a == b)
        return 0;
    return euler_tour[beg[a]].first + euler_tour[beg[b]].first - 2 * euler_tour[beg[lca(a,b)]].first;
}

// CENTROID
vector<int> centroid_par;
vector<bool> vis;
vector<int> siz;

int get_siz(int curr, int par) {
    siz[curr] = 1;
    for (int a : graph[curr])
        if (!vis[a] and a != par)
            siz[curr] += get_siz(a, curr);
    return siz[curr];
}

int get_centroid(int curr, int par, int size_of_subtree) {
    for (int a : graph[curr]) 
        if (!vis[a] and a != par and siz[a] * 2 > size_of_subtree)
            return get_centroid(a, curr, size_of_subtree);
    return curr;
}

void init_centroids(int curr, int CP) {
    int size_of_subtree = get_siz(curr, 0);
    int centroid = get_centroid(curr, 0, size_of_subtree);
    vis[centroid] = 1;
    centroid_par[centroid] = CP;
    for (int a : graph[centroid])
        if (!vis[a])
            init_centroids(a, centroid);
}

// queries

vector<int> best;
void full_init_centroids() {
    centroid_par.resize(n + 1);
    vis.resize(n + 1);
    siz.resize(n + 1);
    init_centroids(1, 0);
}

void change_col(int curr, int changed) {
    if (curr == 0)
        return;
    best[curr] = min(best[curr], distance(changed, curr));
    change_col(centroid_par[curr], changed);
} 

int query(int curr, int og) {
    if (curr == 0)
        return 1e9;
    return min(best[curr] + distance(og, curr), query(centroid_par[curr], og));
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int q;
    cin >> n >> q;
    best.resize(n + 1, 1e9);
    graph.resize(n + 1);
    for (int i = 2; i <= n; i++) {
        int f, t;
        cin >> f >> t;
        graph[f].push_back(t);
        graph[t].push_back(f);
    }

    init_lca();
    full_init_centroids();
    change_col(1, 1);
    while (q--) {
        int t;
        cin >> t;
        if (t == 1) {
            int node;
            cin >> node;
            change_col(node, node);
        } else {
            int node;
            cin >> node;
            cout << query(node, node) << "\n";
        }
    }
}