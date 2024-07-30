#include <bits/stdc++.h>
#define mp make_pair
#define all(a) a.begin(), a.end()

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

const int K = 20;

struct UFDS {
    vector<int> ufds;

    UFDS() {}
    UFDS(int n) {
        ufds = vector<int>(n + 1);
        iota(all(ufds), 0);
    }

    int find(int a) {
        if (ufds[a] == a)
            return a;
        return ufds[a] = find(ufds[a]);
    }

    void merge(int a, int b) {
        ufds[find(a)] = find(b);
    }
};

struct edge {
    int f, t, w, here;

    edge() {}
    edge(int F, int T, int W, int HERE) {
        f = F, t = T, w = W, here = HERE;
    }

    bool operator<(const edge& b) const {
        if (b.w == w)   
            return here > b.here;
        return w > b.w;
    }
};

pii merge(pii top, pii bottom) {
    return pii(top.first, max(top.second, bottom.second));
}

vector<vector<pii> > graph;
vector<ll> height;
vector<vector<pii> > lift;

void dfs(int curr) {
    for (int k = 1; k < K; k++)
        lift[k][curr] = merge(lift[k - 1][lift[k - 1][curr].first], lift[k - 1][curr]);

    for (auto &[t, w] : graph[curr]) {
        if (lift[0][curr].first == t)
            continue;
        height[t] = height[curr] + 1;
        lift[0][t] = pii(curr, w);
        dfs(t);
    }
}

int max_on_path(int a, int b) {
    if (height[a] > height[b]) // b is lower
        swap(a, b);
    int diff = height[b] - height[a];
    pii b_path(b, -1);
    for (int bit = 0; bit < K; bit++)
        if ((1 << bit) & diff)
            b_path = merge(lift[bit][b_path.first], b_path);
    if (b_path.first == a)
        return b_path.second;
    
    pii a_path(a, -1);
    for (int bit = K - 1; bit >= 0; bit--) {
        if (lift[bit][a_path.first].first == lift[bit][b_path.first].first)
            continue;
        a_path = merge(lift[bit][a_path.first], a_path);
        b_path = merge(lift[bit][b_path.first], b_path);
    }
    a_path = merge(lift[0][a_path.first], a_path);
    b_path = merge(lift[0][b_path.first], b_path);
    return max(a_path.second, b_path.second);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    ll n, m, d;
    cin >> n >> m >> d;
    graph = vector<vector<pii> > (n + 1);
    lift = vector<vector<pii> > (K, vector<pii>(n + 1));
    height = vector<ll>(n + 1);
    UFDS ufds(n);
    vector<edge> og;
    priority_queue<edge> q;
    for (int i = 0; i < n - 1; i++) {
        int f, t, w;
        cin >> f >> t >> w;
        q.push(edge(f, t, w, 0));
        og.push_back(edge(f, t, w, 0));
    }

    for (int i = 0; i < m - (n - 1); i++) {
        int f, t, w;
        cin >> f >> t >> w;
        q.push(edge(f, t, w, 1));
    }

    int num = 0;
    multiset<ll> weights;
    while (!q.empty()) {
        edge e = q.top(); q.pop();
        if (ufds.find(e.f) == ufds.find(e.t))
            continue;
        weights.insert(e.w);
        ll rw = e.w;
        if (e.here == 0)
            rw = -1;
        graph[e.f].push_back(pii(e.t, rw));
        graph[e.t].push_back(pii(e.f, rw));
        ufds.merge(e.f, e.t);
        num += e.here;
    }
    dfs(1);

    ll old_sum = accumulate(all(weights), 0LL);
    ll best_possible = old_sum - min(d, *prev(weights.end()));
    int found = 0;
    for (auto &[f, t, w, trash] : og) {
        ll max_rem = max_on_path(f, t);
        if (max_rem == -1)
            continue;
        weights.erase(weights.find(max_rem));
        weights.insert(w);
        ll neww = old_sum - max_rem + w;
        neww -= min(*prev(weights.end()), d);
        if (neww == best_possible)
        {
            found = 1;
            break;
        }
        weights.erase(weights.find(w));
        weights.insert(max_rem);
    }

    cout << num - found << "\n";
}