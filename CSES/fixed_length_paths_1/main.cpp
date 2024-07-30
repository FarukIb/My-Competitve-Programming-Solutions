#include <bits/stdc++.h>
#define mp make_pair
#define all(a) a.begin(), a.end()

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

int n, k;
vector<int> vis;
vector<vector<int> > graph;
vector<int> depth_cnt;
vector<int> sz;
ll out = 0;
int max_depth = 0;
void reset_depth_cnt_and_update_siz(int curr, int par, int depth) {
    if (depth > k)
        return;
    depth_cnt[depth] = 0;
    max_depth = max(max_depth, depth);
    sz[curr] = 1;
    for (int a : graph[curr])
        if (!vis[a] and a != par)
            reset_depth_cnt_and_update_siz(a, curr, depth + 1), sz[curr]+= sz[a];
}

void update_depth_cnt(int curr, int par, int depth) {
    if (depth > k)
        return;
    depth_cnt[depth]++;
    for (int a : graph[curr])
        if (!vis[a] and a != par)
            update_depth_cnt(a, curr, depth + 1);
}

void decrease(int curr, int par, int depth) {
    if (depth > k)
        return;
    depth_cnt[depth]--;
    for (int a : graph[curr])
        if (!vis[a] and a != par)
            decrease(a, curr, depth + 1);
}

void add_to_cnt(int curr, int par, int depth) {
    if (depth > k)
        return;
    for (int a : graph[curr])
        if (!vis[a] and a != par)
            add_to_cnt(a, curr, depth + 1);
    if (k - depth >= 0 and k - depth <= max_depth)
        out += depth_cnt[k - depth];
}

int find_centroid(int curr, int par, int subt_size) {
    for (int a : graph[curr])
        if (!vis[a] and a != par and sz[a] * 2 > subt_size)
            return find_centroid(a, curr, subt_size);
    return curr;
}

void dfs(int curr) {
    reset_depth_cnt_and_update_siz(curr, 0, 0);
    int centroid = find_centroid(curr, 0, sz[curr]);
    max_depth = 0;
    if (k > sz[curr])
        return;
    reset_depth_cnt_and_update_siz(centroid, 0, 0);
    update_depth_cnt(centroid, 0, 0);
    vis[centroid] = true;
    depth_cnt[0] = 2;
    for (int a : graph[centroid]) {
        if (vis[a])
            continue;
        decrease(a, centroid, 1);
        add_to_cnt(a, centroid, 1);
        update_depth_cnt(a, centroid, 1);
    }
    for (int a : graph[centroid])
        if (!vis[a])
            dfs(a);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    cin >> n >> k;
    vis.resize(n+1);
    graph.resize(n+1);
    sz.resize(n+1);
    depth_cnt.resize(n+1);
    for (int i = 1; i < n; i++) {
        int f, t;
        cin >> f >> t;
        graph[f].push_back(t);
        graph[t].push_back(f);
    }
    dfs(1);
    cout << out / 2<< "\n";
}