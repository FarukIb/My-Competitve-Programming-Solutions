#include <bits/stdc++.h>
#define pii pair<ll, ll>
#define ll long long
#define ld long double

using namespace std;

struct seggy {
    vector<ll> tree;
    vector<ll> lazy;
    vector<ll> sett;
    ll n;

    seggy(vector<ll> arr) {
        n = arr.size();
        tree.resize(n * 4, 0);
        lazy.resize(n * 4, 0);
        sett.resize(n * 4, 0);
        build(1, 0, n - 1, arr);
    }

    void build(ll idx, ll l, ll r, vector<ll> &arr) {
        if (l == r)
        {
            tree[idx] = arr[l];
            return;
        }
        ll mid = (l + r) / 2;
        build(idx * 2 + 1, l, mid, arr);
        build(idx * 2 + 2, mid + 1, r, arr);
        tree[idx] = tree[idx * 2 + 1] + tree[idx * 2 + 2];
    }

    void push(ll idx, ll l, ll r) {
        if (sett[idx] != 0){
            tree[idx] = (r - l + 1) * sett[idx];
            if (l != r)
                sett[idx * 2 + 1] = sett[idx], sett[idx * 2 + 2] = sett[idx], 
                lazy[idx * 2 + 1] = 0, lazy[idx * 2 + 2] = 0;
            sett[idx] = 0;
        }

        tree[idx] += lazy[idx] * (r - l + 1);
        if (l != r)
            lazy[idx * 2 + 1] += lazy[idx], lazy[idx * 2 + 2] += lazy[idx];
        lazy[idx] = 0;
    }

    void _update(ll l, ll r, ll L, ll R, ll idx, ll val) {
        push(idx, l, r);
        if (r < L || l > R)
            return;
        if (l >= L && r <= R) {
            lazy[idx] += val;
            push(idx, l, r);
            return;
        }
        ll mid = (l + r) / 2;
        _update(l, mid, L, R, idx * 2 + 1, val);
        _update(mid + 1, r, L, R, idx * 2 + 2, val);
        tree[idx] = tree[idx * 2 + 1] + tree[idx * 2+ 2];
    }

    void update(ll l, ll r, ll val) {
        _update(0, n - 1, l, r, 1, val);
    }

    void _set(ll l, ll r, ll L, ll R, ll idx, ll val) {
        push(idx, l, r);
        if (r < L || l > R)
            return;
        if (l >= L && r <= R) {
            sett[idx] = val, lazy[idx] = 0;
            push(idx, l, r);
            return;
        }
        ll mid = (l + r) / 2;
        _set(l, mid, L, R, idx * 2 + 1, val);
        _set(mid + 1, r, L, R, idx * 2 + 2, val);
        tree[idx] = tree[idx * 2 + 1] + tree[idx * 2+ 2];
    }

    void set(ll l, ll r, ll val) {
        _set(0, n - 1, l, r, 1, val);
    }

    ll _query(ll l, ll r, ll L, ll R, ll idx) {
        push(idx, l, r);
        if (r < L || l > R)
            return 0;
        if (l >= L && r <= R)
            return tree[idx];
        ll mid = (l + r) / 2;
        ll sum = _query(l, mid, L, R, idx * 2 + 1) + 
                 _query(mid + 1, r, L, R, idx * 2 + 2);
        tree[idx] = tree[idx * 2 + 1] + tree[idx * 2 + 2];
        return sum;
    }

    ll query(ll l, ll r) {
        return _query(0, n - 1, l, r, 1);
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    ll n, q;
    cin >> n >> q;
    vector<ll> arr(n);
    for (ll i = 0; i < n; i++)
        cin >> arr[i];
    seggy seg(arr);
    while (q--) {
        char typ;
        cin >> typ;
        if (typ == '1') {
            ll l, r, val;
            cin  >> l >> r >> val;
            l--, r--;
            seg.update(l, r, val);
        }
        else if (typ == '3') {
            ll l, r;
            cin >> l >> r;
            l--, r--;
            cout << seg.query(l, r) << endl;
        }
        else {
            ll l, r, val;
            cin >> l >> r >> val;
            l--, r--;
            seg.set(l, r, val);
        }
    }
}
