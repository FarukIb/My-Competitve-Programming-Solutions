#include <bits/stdc++.h>
#define mp make_pair
#define all(a) a.begin(), a.end()

using namespace std;

typedef long long ll;
typedef pair<ll, ll> pii;

const int K = 20;

struct info {
    ll length, min_cost, top_node;
    info() {length=0,min_cost=0;}
    info(ll a, ll b, ll c) {length = a, min_cost = b, top_node = c;}
};

info merge(info lower, info higher) {
    return info(lower.length + higher.length, min(lower.min_cost, higher.min_cost + lower.length), higher.top_node);
}

vector<pair<pii, ll> > edges;
vector<vector<pii> > graph;
vector<vector<info> > lift;
vector<int> in_time;
vector<int> out_time;
vector<bool> is_shop;

int tim = 0;
ll dfs(int curr, ll par, ll edge_cst) {
    ll min_cost = 1e18;
    if (is_shop[curr])
        min_cost = 0;
    in_time[curr] = tim;
    for (auto &[a, w] : graph[curr]) {
        if (a == par)
            continue;
        tim++;
        min_cost = min(min_cost, dfs(a, curr, w) + w);
    }
    lift[0][curr] = info(edge_cst, min_cost, par);
    out_time[curr] = ++tim;
    return min_cost;
}

void dfs2(int curr, ll par) {
    for (int i = 1; i < K; i++)
        lift[i][curr] = merge(lift[i - 1][curr], lift[i-1][lift[i-1][curr].top_node]);
    for (auto &[a, w] : graph[curr])
        if (a != par)
            dfs2(a, curr);
}

bool is_ancestor(int a, int b) {
    return in_time[a] <= in_time[b] and out_time[a] >= out_time[b];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int n, s, q, e;
    cin >> n >> s >> q >> e;
    graph = vector<vector<pii> > (n+1);
    in_time.resize(n+1);
    in_time[0] = -1e9;
    out_time.resize(n+1);
    out_time[0] = 1e9;
    edges.resize(n+1);
    is_shop.resize(n+1);
    lift.resize(K, vector<info>(n+1));

    for (int i = 0; i < n - 1; i++) {
        cin >> edges[i].first.first >> edges[i].first.second >> edges[i].second;
        graph[edges[i].first.first].push_back({edges[i].first.second, edges[i].second});
        graph[edges[i].first.second].push_back({edges[i].first.first, edges[i].second});
    }

    for (int i = 0; i < s; i++) {
        int guy;
        cin >> guy;
        is_shop[guy] = true;
    }
    dfs(e, 0, 0);
    dfs2(e, 0);

    while (q--) {
        int block, r;
        cin >> block >> r;
        block--;

        pii block_edge = edges[block].first;
        if (in_time[block_edge.first] < in_time[block_edge.second])
            swap(block_edge.first, block_edge.second);
        int block_node = block_edge.first;
    
        // checking if you can leave
        if (!is_ancestor(block_node, r)) {
            cout << "escaped\n";
            continue;
        }
        block_node = lift[0][block_edge.second].top_node;
        // now_bin_lifting
        info ans = lift[0][r];
        for (int i = K - 1; i >= 0; i--) {
            info top = lift[i][ans.top_node];
            if (is_ancestor(top.top_node, block_node))
                continue;
            ans = merge(ans, top);
        }

        if (ans.min_cost >= 1e18)
            cout << "oo\n";
        else
            cout << ans.min_cost << "\n";
    }
}