#include <bits/stdc++.h>
#define pii pair<ll, ll>
#define ll long long
#define ld long double

using namespace std;

struct node {
    ll pref, sum, l;

    node() {}
    node(ll val, ll idx) {pref = max(0LL, val), sum = val, l = idx;}
};

node merge(node a, node b) {
    if (a.l == -1e18 + 3)
        return b;
    else if (b.l == -1e18 + 3)
        return a;
    if (a.l > b.l)
        swap(a, b);
    
    node neww;
    neww.sum = a.sum + b.sum;
    neww.pref = max(a.pref, a.sum + b.pref);
    neww.l = a.l;

    return neww;
}

struct seggy {
    vector<node> tree;
    ll n;

    seggy(vector<ll> arr) {
        n = arr.size();
        tree.resize(n * 2);
        for (ll i = n; i < 2 * n; i++)
            tree[i] = node(arr[i - n], i - n);
        for (ll i = n - 1; i > 0; i--)
            tree[i] = merge(tree[i * 2], tree[i * 2 + 1]);
    }

    void mod(ll idx, ll val) {
        idx += n, tree[idx] = node(val, idx - n);
        for (idx /= 2; idx > 0; idx /= 2)
            tree[idx] = merge(tree[idx * 2], tree[idx * 2 + 1]);
    }

    ll query(ll l, ll r) {
        node ansl, ansr; ansl.l = -1e18 + 3, ansr.l = -1e18 + 3;
        for (l += n, r += n + 1; l < r; l /= 2, r /= 2) {
            if (l & 1)
                ansl = merge(ansl, tree[l++]);
            if (r & 1)
                ansr = merge(tree[--r], ansr);
        }
        return merge(ansl, ansr).pref;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    //freopen("a.in", "r", stdin);
    //freopen("a.out", "w", stdout);

    ll n, q;
    cin >> n >> q;

    ll oldn = n;
    //if (!((n & (n - 1)) == 0)) {
    //    n = 1 << (32 - __builtin_clz(n));
    //}
    vector<ll> arr(n, 0);
    for (ll i = 0; i < oldn; i++)
        cin >> arr[i];
    
    seggy seg(arr);
    while (q--) {
        ll type;
        cin >> type;

        if (type == 1) {
            ll idx, val;
            cin >> idx >> val;
            seg.mod(idx - 1, val);
        }
        else {
            int l, r;
            cin >> l >> r;
            cout << max(0LL, seg.query(--l, --r)) << endl;
        }
    }
}
