#include <bits/stdc++.h>
#define mp make_pair

using namespace std;

typedef long long ll;
typedef pair<ll, ll> pii;

struct seggy {
    vector<ll> tree;
    vector<ll> lazy;
    ll n;

    seggy(vector<ll> arr) {
        n = arr.size();
        tree.resize(n * 4, 0);
        lazy.resize(n * 4, 0);
        for (ll i = 0; i < n; i++)
            update(i, i, arr[i]);
    }

    void push(ll idx, ll l, ll r) {
        ll val = lazy[idx];
        tree[idx] += val;
        lazy[idx] = 0;
        if (l != r) {
            lazy[idx * 2] += val;
            lazy[idx * 2 + 1] += val; 
        }
    }

    void update_h(ll l, ll r, ll L, ll R, ll idx, ll val) {
        push(idx, l, r);
        if (r < L || l > R)
            return;
        if (l >= L and r <= R) {
            lazy[idx] += val;
            push(idx, l, r);
            return;
        }
        ll mid = (l + r) / 2;
        update_h(l, mid, L, R, idx * 2, val);
        update_h(mid + 1, r, L, R, idx * 2 + 1, val);
        tree[idx] = max(tree[idx * 2], tree[idx * 2 + 1]);
    }

    void update(ll l, ll r, ll val) {
        update_h(0, n - 1, l, r, 1, val);
    }
    
    ll query_h(ll l, ll r, ll L, ll R, ll idx) {
        push(idx, l, r);
        if (r < L || l > R)
            return 0;
        if (l >= L and r <= R)
            return tree[idx];
        ll mid = (l + r) / 2;
        ll out = max(query_h(l, mid, L, R, idx * 2)
                 , query_h(mid + 1, r, L, R, idx * 2 + 1));
        tree[idx] = max(tree[idx * 2], tree[idx * 2 + 1]);
        return out;
    }

    ll query(ll l, ll r) {
        return query_h(0, n - 1, l, r, 1);
    }
};

vector<ll> dfs_arr_dist;
vector<ll> num_children;
vector<ll> dfs_arr_idx;
vector<ll> par;

vector<vector<pii> > graph;
void dfs(ll curr, ll weight) {
    dfs_arr_idx[curr] = dfs_arr_dist.size();
    dfs_arr_dist.push_back(weight);
    ll my_num_child = 1;
    for (pii s : graph[curr]) {
        if (s.first == par[curr])
            continue;
        par[s.first] = curr;
        dfs(s.first, weight + s.second);
        my_num_child += num_children[s.first];
    }
    num_children[curr] = my_num_child;
}

ll get_subtree_val(const ll s, seggy& dfs_seg) {
    return dfs_seg.query(dfs_arr_idx[s], 
            dfs_arr_idx[s] + num_children[s] - 1);
}

pii get_range(const ll s) {
    return {dfs_arr_idx[s], 
            dfs_arr_idx[s] + num_children[s] - 1};
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    ll n, q; ll w;
    cin >> n >> q >> w;
    num_children.resize(n + 1, 0);
    dfs_arr_idx.resize(n + 1, 0);
    par.resize(n + 1, 0);
    graph.resize(n + 1);

    vector<pii> edges;
    for (ll i = 1; i < n; i++) {
        ll f, t, w;
        cin >> f >> t >> w;
        edges.push_back({f, t});
        graph[f].push_back({t, w});
        graph[t].push_back({f, w});
    }
    for (ll i = 1; i <= n; i++)
        sort(graph[i].begin(), graph[i].end());

    dfs(1, 0);
    seggy dfs_seg(dfs_arr_dist);
    multiset<ll> dps;
    vector<ll> one_idxs;
    vector<ll> one_idxs2;
    for (pii s : graph[1]) {
        dps.insert(
            get_subtree_val(s.first, dfs_seg));
        one_idxs.push_back(dfs_arr_idx[s.first]);
        one_idxs2.push_back(s.first);
    }
    sort(one_idxs.begin(), one_idxs.end());

    ll last = 0;
    while (q--) {
        ll e, d;
        cin >> d >> e;
        d += last;
        e += last;
        d %= (n - 1);
        e %= w;

        pii myedge = edges[d]; // first guy is parent
        if (par[myedge.second] != myedge.first)
            swap(myedge.first, myedge.second);
        ll guy = myedge.second;

        ll idx_of_edge = lower_bound(
            graph[guy].begin(), 
            graph[guy].end(),
             pii(myedge.first, 0))
         - graph[guy].begin();

        ll change = e - graph[guy][idx_of_edge].second;
        graph[guy][idx_of_edge].second = e;

        // getting subtree
        ll my_idx = dfs_arr_idx[guy];
        ll subtree = one_idxs2[prev(upper_bound(one_idxs.begin(),
            one_idxs.end(),
            my_idx
        )) - one_idxs.begin()];

        // chaning val in multiset
        ll curr_val = get_subtree_val(subtree, dfs_seg);
        dps.erase(dps.lower_bound(curr_val));

        // changing val in seg and adding back to mulitset
        dfs_seg.update(get_range(guy).first, get_range(guy).second, change);
        dps.insert(get_subtree_val(subtree, dfs_seg));

        ll ans = *prev(dps.end());
        if (dps.size() > 1) {
            ans = max(ans, *prev(dps.end()) + *prev(prev(dps.end())));
        }
        cout << ans << "\n";
        last = ans;
    }
}