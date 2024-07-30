#include <bits/stdc++.h>
#define mp make_pair
#define all(a) a.begin(), a.end()

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;


vector<int> tre; int curr;
struct seggy {
    int n, L;

    seggy() {}
    seggy(vector<int> &arr) {
        L = curr; 
        n = arr.size(); curr += 2*n;
        for (int i = n; i < 2 * n; i++)
            tre[i + L] = arr[i - n];
        for (int i = n - 1; i > 0; i--)
            tre[i + L] = max(tre[i*2+L], tre[i*2+1+L]);
    }

    int query(int l, int r) {
        if (l == 0 and r == n - 1)
            return tre[1+L];
        if (l > r)
            return 0;
        int maxi = 0;
        for (l += n, r += n + 1; l < r; l/= 2, r/= 2) {
            if (l & 1)
                maxi = max(maxi, tre[L+(l++)]);
            if (r & 1)
                maxi = max(maxi, tre[L+(--r)]);
        }
        return maxi;
    }

    void update(int val, int idx) {
        for (idx += n, tre[idx+L] = val, idx /= 2; idx > 0; idx /= 2)
            tre[idx+L] = max(tre[L+idx * 2], tre[L+idx * 2 + 1]);
    }
};

vector<vector<pii> > tree;
vector<int> depth, seg_idx, head, pos, par;
vector<seggy> seggs;

vector<int> heavy;
vector<int> cost;
int dfs(int curr, int h) {
    pii heavies(-1, -1); int my = 1;
    for (auto &[t, c] : tree[curr]) {
        if (t == h)
            continue;
        depth[t] = depth[curr] + 1, par[t] = curr;
        int siz = dfs(t, curr); my += siz;
        heavies = max(heavies, {siz, t});
        cost[t] = c;
    }
    heavy[curr] = heavies.second;
    return my;
}

int path_idxs = 0;
vector<int> path;
void decomp(int curr, int h, int p) {
    pos[curr] = path.size();
    head[curr] = h;
    seg_idx[curr] = seggs.size();
    path.push_back(cost[curr]);
    if (heavy[curr] == -1) {
        seggs.push_back(seggy(path));
        return;
    } else {
        decomp(heavy[curr], h, curr);
    }
    for (auto &[t,c] : tree[curr]) {
        if (t == p || t == heavy[curr])
            continue;
        path.clear();
        decomp(t, t, curr);
    }
}

void update(int idx, int val) { seggs[seg_idx[idx]].update(val, pos[idx]); }

int query(int a, int b) {
    int out = 0;
    for (; head[a] != head[b]; b = par[head[b]]) {
        if (depth[head[a]] > depth[head[b]])
            swap(a, b);
        out = max(out, 
            seggs[seg_idx[head[b]]].query(pos[head[b]], pos[b]));
    }
    if (depth[a] > depth[b])
        swap(a, b);
    out = max(out,
        seggs[seg_idx[a]].query(pos[a] + 1, pos[b]));
    return out;
}

void solve() {
    int n;
    cin >> n;
    tre = vector<int>(2*n,0); curr = 0;
    tree = vector<vector<pii> > (n + 1);
    depth = seg_idx = head = pos = par = heavy = cost = vector<int>(n+1, -1);
    depth[1] = 0, par[1] = 0;
    seggs.clear();
    path.clear();
    path_idxs = 0;

    vector<int> edge_idx(n);
    vector<pii> edges;
    for (int i = 0; i < n - 1; i++) {
        int f, t, c;
        cin >> f >> t >> c;
        edges.push_back({f, t});
        tree[f].push_back({t, c});
        tree[t].push_back({f, c});
    }
    dfs(1, 0);
    decomp(1, 1, 0);
    for (int i = 0; i < n - 1; i++)
    {
        if (depth[edges[i].first] > depth[edges[i].second])
            swap(depth[edges[i].first], depth[edges[i].second]);
        edge_idx[i] = edges[i].second;
    }

    while (true) {
        string type;
        cin >> type;
        if (type == "DONE")
            break;
        else if (type == "QUERY") {
            int a, b;
            cin >> a >>b;
            cout << query(a, b) << endl;
        } else {
            int idx, val;
            cin >> idx >> val;
            update(edge_idx[idx - 1], val);
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int t;
    cin >> t;
    while (t--) {solve();}
}