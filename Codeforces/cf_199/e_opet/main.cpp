#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> pii;

const int INF = 1e9;

vector<vector<int> > tree;
vector<vector<pii> > ancestors;
vector<int> subt_size;

vector<bool> vis;
int get_subt_size(int curr, int par) {
    int siz = 1;
    for (int a : tree[curr]) {
        if (a == par || vis[a])
            continue;
        siz += get_subt_size(a, curr);
    }
    return subt_size[curr] = siz;
}

int get_centroid(int curr, int par, int siz) {
    for (int a : tree[curr]) {
        if (a == par || vis[a])
            continue;
        if (subt_size[a] * 2 > siz)
            return get_centroid(a, curr, siz);
    }
    return curr;
}

void get_dists(int curr, int centroid, int par, int dist) {
    for (int a : tree[curr]) {
        if (a == par || vis[a])
            continue;
        get_dists(a, centroid, curr, dist + 1);
    }
    ancestors[curr].push_back(pii(centroid, dist));
}

void init_centroid(int curr) {
    int centroid = get_centroid(curr, -1, get_subt_size(curr, -1));
    for (int a : tree[centroid])
        if (!vis[a])
            get_dists(a, centroid, centroid, 1);
    vis[centroid] = true;
    for (int a : tree[centroid])
        if (!vis[a]) 
            init_centroid(a);
}

vector<int> min_dist;
void upd(int curr) {
    for (auto &[guy, dist] : ancestors[curr])
        min_dist[guy] = min(min_dist[guy], dist);
    min_dist[curr] = 0;
}

int get_dist(int curr) {
    int out = min_dist[curr];
    for (auto &[guy, dist] : ancestors[curr])
        out = min(out, min_dist[guy] + dist);
    return out;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int n, m;
    cin >> n >> m;
    tree = vector<vector<int> > (n + 1);
    subt_size = min_dist = vector<int> (n + 1, INF);
    vis = vector<bool> (n + 1);
    ancestors = vector<vector<pii> > (n + 1);
    for (int i = 1; i < n; i++) {
        int f, t;
        cin >> f >> t;
        tree[f].push_back(t);
        tree[t].push_back(f);
    }

    init_centroid(1);
    upd(1);
    while (m--) {
        int t;
        cin >> t;
        if (t == 1) {
            int x;
            cin >> x;
            upd(x);
        } else {
            int x;
            cin >> x;
            cout << get_dist(x) << "\n";
        }
    }
}