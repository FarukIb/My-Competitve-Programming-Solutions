#include <bits/stdc++.h>
#define mp make_pair

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

int n;
struct seggy {
    vector<int> lazy;
    vector<pii> tree;

    seggy(vector<pii> arr) {
        n = arr.size();
        tree.resize(n * 4);
        lazy.resize(n * 4);
        build(1, 0, n - 1, arr);
    }

    void build(int idx, int l, int r, vector<pii>&arr) {
        if (l == r)
        {
            tree[idx] = mp(arr[l].first, -arr[l].second);
            return;
        }
        int mid = (r + l) / 2;
        build(idx * 2, l, mid, arr);
        build(idx * 2 + 1, mid + 1, r, arr);
        tree[idx] = max(tree[idx * 2], tree[idx * 2 + 1]);
    }

    void send(int &idx, int &l, int &r) {
        tree[idx].first += lazy[idx];
        if (l != r) {
            lazy[idx * 2] += lazy[idx];
            lazy[idx * 2 + 1] += lazy[idx];
        }

        lazy[idx] = 0;
    }

    void b_update(int idx, int l, int r, int &L, int &R, int &val) {
        send(idx, l, r);
        if (l > R || r < L)
            return;
        if (l >= L && r <= R) {
            lazy[idx] += val;
            send(idx, l, r);
            return;
        }

        int mid = (r + l) / 2;
        b_update(idx * 2, l, mid, L, R, val);
        b_update(idx * 2 + 1, mid + 1, r, L, R, val);
        tree[idx] = max(tree[idx * 2], tree[idx * 2 + 1]);
    }

    void update(int l, int r, int val) {
        b_update(1, 0, n - 1, l, r, val);
    }

    pii b_query(int idx, int l, int r, int &L, int &R) {
        send(idx, l, r);
        if (l >R || r < L)
            return pii(-2e9, -2e9);
        if (l >= L && r <= R)
            return tree[idx];
        int mid = (r + l) / 2;
        pii q1 = b_query(idx * 2, l, mid, L, R);
        pii q2 = b_query(idx * 2 + 1, mid + 1, r, L, R);
        tree[idx] = max(tree[idx * 2], tree[idx * 2 + 1]);
        return max(q1, q2);
    }

    pii query(int l, int r) {
        pii p = b_query(1, 0, n - 1, l, r);
        return p;
    }
};

vector<vector<int> > graph;
vector<pii> dfsarr; // first is the node second is beauti[i] - depth (we start at 1)
vector<int> dfs_idx;
vector<int> num_child;
vector<int> beauty;

void make_dfsarr(int curr, int par, int depth) {
    dfs_idx[curr] = dfsarr.size();
    dfsarr.push_back(pii(beauty[curr] - depth, curr));
    for (int x : graph[curr]) {
        if (par != x)
        {
            make_dfsarr(x, curr, depth + 1);
            num_child[curr] += num_child[x] + 1;
        }
    }
}

vector<int> pnt;
void do_dp(int curr, int par, seggy &seg) {
    if (dfs_idx[curr] == 0)
        pnt[curr] = -seg.query(1, n - 1).second;
    else if (dfs_idx[curr] == n - 1)
        pnt[curr] = -seg.query(0, n - 2).second;
    else 
        pnt[curr] = -max(seg.query(0, dfs_idx[curr] - 1), seg.query(dfs_idx[curr] + 1, n - 1)).second;
    
    for (int x : graph[curr]) {
        if (x == par)
            continue;
        // x will never be 1
        int l = dfs_idx[x] + 1, r = dfs_idx[x] + num_child[x];
        if (l <= r) {
            seg.update(0, l - 1, -1);
            seg.update(l, r, 1);
            if (r != n - 1)
                seg.update(r + 1, n - 1, -1);
        }
        do_dp(x, curr, seg);
        if (l <= r) {
            seg.update(0, l - 1, 1);
            seg.update(l, r, -1);
            if (r != n - 1)
                seg.update(r + 1, n - 1, +1);
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    ll k;
    cin >> n >> k;
    beauty.resize(n + 1, 0);
    graph.resize(n + 1);
    dfs_idx.resize(n + 1);
    num_child.resize(n + 1, 0);
    pnt.resize(n + 1);

    for (int i = 0; i < n; i++)
        cin >> beauty[i + 1];
    for (int i = 0; i < n - 1; i++) {
        int f, t;
        cin >> f >> t;
        graph[f].push_back(t);
        graph[t].push_back(f);
    }

    make_dfsarr(1, -1, 0);

    seggy seg(dfsarr);
    do_dp(1, -1, seg);

    int s = 1;
    for (int i = 0; i < k; i++)
        s = pnt[s] ;
    
    cout << s << "\n";
}