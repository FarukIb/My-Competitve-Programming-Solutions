#include <bits/stdc++.h>
#define mp make_pair
#define all(a) a.begin(), a.end()

using namespace std;

typedef long long ll;
typedef pair<ll, ll> pii;

pii merge(pii a, pii b) {
    if (a.first == b.first)
        return {a.first, a.second + b.second};
    return max(a, b);
}

struct seggy {
    ll n;
    vector<pii> tree;
    vector<ll> lazy;
 
    seggy(ll N) {
        n = N;
        tree.resize(n*4);
        lazy.resize(n*4);
        build(0, n - 1, 1);
    }

    void build(ll l, ll r, ll idx) 
    {
        if (l == r) {
            tree[idx] = mp(0, 1);
            return;
        }
        ll mid = (l + r) / 2;
        build(l, mid, idx*2);
        build(mid + 1, r, idx*2+1);
        tree[idx] = max(tree[idx*2], tree[idx*2+1]);
    }
 
 
    void push(ll idx, ll l, ll r) {
        if (lazy[idx] == 0)
            return;
        tree[idx].first += lazy[idx];
        if (l != r) {
            lazy[idx*2] += lazy[idx];
            lazy[idx*2+1] += lazy[idx];
        }
        lazy[idx] = 0;
    }
 
    void update(ll l, ll r, ll L, ll R, ll idx, ll val) {
        push(idx, l, r);
        if (l > R || r < L)
            return;
        if (l >= L and r <= R) {
            lazy[idx] += val;
            push(idx, l, r);
            return;
        }
        ll mid = (l + r) / 2;
        update(l, mid, L, R, idx*2, val);
        update(mid + 1, r, L, R, idx*2+1, val);
        tree[idx] = merge(tree[idx*2], tree[idx*2+1]);
    }
 
    void update(ll l, ll r, ll val) {
        update(0, n - 1, l, r, 1, val);
    }
 
    pii query(ll l, ll r, ll L, ll R, ll idx) {
        push(idx,l, r);
        if (l > R || r < L)
            return mp(0, 0);
        if (l >= L and r <= R) 
            return tree[idx];
        ll mid = (l + r) / 2;
        pii my = merge(query(l, mid, L, R, idx*2), query(mid + 1, r, L, R, idx*2+1));
        tree[idx] = merge(tree[idx*2], tree[idx*2+1]);
        return my;
    }
 
    pii query(ll l, ll r) {
        return query(0, n - 1, l, r, 1);
    }
};

void mymaxi(ll &maxi, ll &num, pii neww) {
    if (neww.first == maxi)
        num += neww.second;
    else if (neww.first > maxi)
        maxi = neww.first, num = neww.second;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    ll n, k, q;
    cin >> n >> k >> q;
    vector<ll> a(n);
    vector<ll> b(n);
    for (ll i = 0; i < n; i++)
        cin >> a[i];
    vector<ll> locinb(n + 1);
    for (ll i = 0; i < n; i++)
    {
        cin >> b[i];
        locinb[b[i]] = i;
    }

    for (ll T = 0; T <= q; T++) {
        if (T != 0) {
            ll f;
            cin >> f;
            swap(a[f], a[f - 1]);
        }

        seggy seg(n + 1);
        ll maxi = -1, num = 0;
        for (ll i = 0; i + k <= n; i++) {
            if (i == 0)
            {
                for (ll j = 0; j < i + k; j++)
                    seg.update(max(0LL, locinb[a[j]] - k + 1), min(n - k, locinb[a[j]]), 1);
            } else {
                ll j = i - 1;
                seg.update(max(0LL, locinb[a[j]] - k + 1), min(n - k, locinb[a[j]]), -1);
                j = i + k - 1;
                seg.update(max(0LL, locinb[a[j]] - k + 1), min(n - k, locinb[a[j]]), 1);
            }

            mymaxi(maxi, num, seg.query(0, n - k));
        }
        cout << maxi <<" " << num << "\n";
    }
}