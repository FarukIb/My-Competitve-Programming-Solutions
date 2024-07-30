#include <bits/stdc++.h>
#define mp make_pair

using namespace std;

typedef long long ll;
typedef pair<ll, ll> pii;

struct seggy {
    vector<ll> tree;
    vector<ll> lazy;
    ll n;
    seggy(ll siz, vector<ll> arr) {
        ll ext = 1;
        while (ext < siz)
            ext *= 2;
        n = ext;

        tree.resize(n * 2, 0);
        lazy.resize(n * 2, 0);

        for (ll i = 0; i < siz; i++)
            tree[i + n] = arr[i];
        for (ll i = n - 1; i > 0; i--)
            tree[i] = tree[i * 2] + tree[i * 2 + 1];
    }

    void push(ll l, ll r, ll idx) {
        ll val = lazy[idx];
        tree[idx] += lazy[idx] * (r - l + 1);
        lazy[idx] = 0;
        if (l == r)
            return;
        lazy[idx * 2] += val;
        lazy[idx * 2 + 1] += val; 
    }

    void update_h(ll l, ll r, ll L, ll R, ll idx, ll val) {
        push(l, r, idx);
        if (l >= L && r <= R) {
            lazy[idx] += val;
            push(l, r, idx);
            return;
        }
        if (l > R || r < L)
            return;
        ll mid = (r + l) / 2;
        update_h(l, mid, L, R, idx * 2, val);
        update_h(mid + 1, r, L, R, idx * 2 + 1, val);
        tree[idx] = tree[idx * 2] + tree[idx * 2 + 1];
    }

    void update(ll l, ll r, ll val) {
        update_h(0, n - 1, l, r, 1, val);
    }

    ll query_h(ll l, ll r, ll L, ll R, ll idx) {
        push(l, r, idx);
        if (l >= L && r <= R) {
            return tree[idx];
        }
        if (l > R || r < L)
            return 0;
        ll mid = (r + l) / 2;
        ll a = query_h(l, mid, L, R, idx * 2);
        ll b = query_h(mid + 1, r, L, R, idx * 2 + 1);
        tree[idx] = tree[idx * 2] + tree[idx * 2 + 1];
        return a + b;
    }

    ll query(ll l, ll r) {
        return query_h(0, n - 1, l, r, 1);
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    ll n, q;
    cin >> n >>q;
    vector<ll> arr(n);
    for (ll i = 0; i < n; i++)
        cin >> arr[i];

    seggy seg(n, arr);
    while (q--) {
        ll t;
        cin >> t;
        if (t == 2) {
            ll i;
            cin >> i;
            cout << seg.query(i - 1, i - 1) << endl;
        }
        else {
            ll l, r, val;
            cin >> l >> r >> val;
            seg.update(l - 1, r - 1, val);
        }
    }
}