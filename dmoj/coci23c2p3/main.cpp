#include <bits/stdc++.h>
#define mp make_pair
#define all(a) a.begin(), a.end()

using namespace std;

typedef long long ll;
typedef pair<ll, ll> pii;

struct node {
    ll val, num, lazy;

    node() {val = 0, num = 0, lazy = 0;}
    node(ll V, ll N, ll L) {val = V, num = N, lazy = L;}
};

node merge(node a, node b) {
    return node(a.val + b.val, a.num + b.num, 0);
}

struct seggy {
    vector<node> tree;
    ll n;

    seggy(ll N) {
        n = N;
        tree = vector<node>(n * 4);
    } 

    void push(ll l, ll r, ll idx) {
        tree[idx].val += tree[idx].num * tree[idx].lazy;
        if (l != r)
            tree[idx * 2].lazy += tree[idx].lazy, tree[idx * 2 + 1].lazy += tree[idx].lazy;
        tree[idx].lazy = 0;
    }

    void change_node(ll l, ll r, ll targ, ll idx, bool add, ll v) {
        push(l, r, idx);
        if (l > targ || r < targ)
            return;
        if (l == r) {
            if (!add)
                tree[idx].num = 0, tree[idx].val = 0;
            else
                tree[idx].num = 1, tree[idx].val = v;
            return;
        }
        ll mid = (l + r) / 2;
        change_node(l, mid, targ, idx * 2, add, v);
        change_node(mid + 1, r, targ, idx * 2 + 1, add, v);
        tree[idx] = merge(tree[idx * 2], tree[idx * 2 + 1]);
    }

    void add_node(ll idx, ll val) {
        change_node(0, n - 1, idx, 1, true, val);
    }

    void rem_node(ll idx) {
        change_node(0, n - 1, idx, 1, false, 0);
    } 

    void update(ll l, ll r, ll L, ll R, ll idx, ll v) {
        push(l, r, idx);
        if (l > R || r < L)
            return;
        if (l >= L and r <= R) {
            tree[idx].lazy += v;
            push(l, r, idx);
            return;
        }
        ll mid = (l + r) / 2;
        update(l, mid, L, R, idx * 2, v);
        update(mid + 1, r, L, R, idx * 2 + 1, v);
        tree[idx] = merge(tree[idx * 2], tree[idx * 2 + 1]);
    }

    void update(ll l, ll r, ll val) {
        update(0, n - 1, l, r, 1, val);
    }

    node query(ll l, ll r, ll L, ll R, ll idx) {
        push(l, r, idx);
        if (l > R || r < L)
            return node(0, 0, 0);
        if (l >= L and r <= R)
            return tree[idx];
        ll mid = (l + r) / 2;
        node out = merge(query(l, mid, L, R, idx * 2), query(mid + 1, r, L, R, idx * 2 + 1));
        tree[idx] = merge(tree[idx * 2], tree[idx * 2 + 1]);
        return out;
    }

    node query(ll l, ll r) {
        return query(0, n - 1, l, r, 1);
    }
};

struct query {
    ll idx, val;
    query() {}
    query(ll a, ll b) { idx = a, val = b; }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    ll n, q;
    cin >> n >> q;
    vector<ll> arr(n);
    for (ll i = 0; i < n; i++)
    {
        cin >> arr[i];
        arr[i]--;
    }
    vector<bool> not_here(n);
    vector<query> queries;
    for (ll i = 0; i < q; i++) {
        ll idx;
        cin >> idx;
        idx--;
        not_here[idx] = true;
        query me; me.idx = idx, me.val = arr[idx];
        queries.push_back(me);
    }
    for (ll i = 0; i < n; i++)
        if (!not_here[i])
            queries.push_back({i, arr[i]});
    reverse(all(queries));

    vector<ll> out;
    seggy idx_seg(n), val_seg(n); ll num = 0;
    seggy all_idx_seg(n), all_val_seg(n);
    set<pii> stack; // first is idx second is val
    for (query q : queries)  {
        ll idx = q.idx, val = q.val;
        num++;
        auto it = stack.insert(pii(idx, val)).first;
        idx_seg.update(idx, n - 1, 1);
        all_idx_seg.add_node(idx, 0);
        val_seg.update(val, n - 1, 1);
        all_val_seg.add_node(val, 0);
        if (next(it) != stack.end() and it->second > next(it)->second) {
            stack.erase(it);
            out.push_back(num + idx_seg.query(0, n - 1).val - val_seg.query(0, n - 1).val);
            continue;
        }
        idx_seg.add_node(idx, all_idx_seg.query(0, idx).num - 1);
        val_seg.add_node(val, all_val_seg.query(0, val).num - 1);
        if (it != stack.begin()) {
            while (1) {
                if (prev(it)->second > it->second)
                {
                    idx_seg.rem_node(prev(it)->first);
                    val_seg.rem_node(prev(it)->second);
                    stack.erase(prev(it));
                }
                else
                    break;
            }
        }
        
        out.push_back(num + idx_seg.query(0, n - 1).val - val_seg.query(0, n - 1).val);
    }

    cout << out.back();
    for (ll i = (ll)out.size() - 2; i >= (ll)out.size() - q - 1; i--)
        cout << " " << out[i];

    cout << "\n";
}

// ans je idx - val + 2 ako je sve 0 indeksirano