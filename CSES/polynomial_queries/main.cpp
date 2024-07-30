#include <bits/stdc++.h>
#define mp make_pair

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

struct seggy {
    vector<ll> tree;
    vector<ll> lazy;
    vector<ll> cnt;
    int n;

    seggy(vector<int> init) {
        n = init.size();
        tree.resize(n * 4, 0);
        lazy.resize(n * 4, 0);
        cnt.resize(n * 4, 0);

        build(1, 0, n - 1, init);
    }

    void build(int idx, int l, int r, vector<int> &arr) {
        if (l == r) {
            tree[idx] = arr[l];
            return;
        }
        int mid = (l + r) / 2;
        build(idx * 2 + 1, l , mid, arr);
        build(idx * 2 + 2, mid + 1, r, arr);
        tree[idx] = tree[idx * 2 + 1] + tree[idx * 2 + 2];
    }

    void push(ll l, ll r, int idx) {
        if (cnt[idx] == 0)
            return;
        tree[idx] += lazy[idx] * (r - l + 1) + ((r - l + 1) * (r - l + 2) * cnt[idx]) / 2;
        
        if (l != r) {
            int mid = (r - l + 1) / 2;
            lazy[idx * 2 + 1] += lazy[idx];
            lazy[idx * 2 + 2] += lazy[idx] + (mid + (r - l + 1) % 2) * cnt[idx];
            cnt[idx * 2 + 1] += cnt[idx];
            cnt[idx * 2 + 2] += cnt[idx];
        }

        lazy[idx] = 0;
        cnt[idx] = 0;
    }

    void _update(int l, int r, int L, int R, int idx) {
        push(l, r, idx);
        if (l > R || r < L) 
            return;
        if (l >= L && r <= R) {
            lazy[idx] += l - L;
            cnt[idx]++;
            push(l, r, idx);
            return;
        }

        int mid = (r + l) / 2;
        _update(l, mid, L, R, idx * 2 + 1);
        _update(mid + 1, r, L, R, idx * 2 + 2);
        tree[idx] = tree[idx * 2 + 1] + tree[idx * 2 + 2];
    }

    ll _query(int l, int r, int L, int R, int idx) {
        push(l, r, idx);
        if (l > R || r < L) 
            return 0;
        if (l >= L && r <= R) {
            return tree[idx];
        }

        int mid = (r + l) / 2;
        ll out = _query(l, mid, L, R, idx * 2 + 1) + _query(mid + 1, r, L, R, idx * 2 + 2);
        tree[idx] = tree[idx * 2 + 1] + tree[idx * 2 + 2];
        return out;
    }

    void update(int l, int r) {
        _update(0, n - 1, l, r, 1);
    }

    ll query(int l, int r) {
        return _query(0, n - 1, l, r, 1);
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int n, q;
    cin >> n >>q;
    vector<int>arr(n);
    for (int i = 0; i < n; i++)
        cin >> arr[i];
    seggy seg(arr);
    while (q--) {
        int t, a, b;
        cin >>t >> a >>b;
        a--, b--;
        if (t == 1)
            seg.update(a, b);
        else 
            cout << seg.query(a, b) << endl;
    }
}