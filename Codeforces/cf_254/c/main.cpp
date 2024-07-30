#include <bits/stdc++.h>
#define mp make_pair

using namespace std;
 
typedef long long ll;
typedef pair<int, int> pii;
 
struct seggy {
    vector<ll> tree;
    vector<ll> lazy;
    int n;
 
    seggy() {}
    seggy(int siz) {
        tree.resize(4 * siz, 0);
        lazy.resize(4 * siz, 0);
        n = siz;
    }
 
    void push(int l, int r, int idx) {
        tree[idx] += lazy[idx] * (r - l + 1);
        ll laz = lazy[idx];
        lazy[idx] = 0;
        if (l == r)
            return;
        lazy[idx * 2] += laz;
        lazy[idx * 2 + 1] += laz;
    }
 
    void update_h(int l, int r, int L, int R, int val, int idx) {
        push(l, r, idx);
        if (l >= L && r <= R) {
            lazy[idx] += val;
            push(l, r, idx);
            return;
        }
        if (r < L || l > R)
            return;
        int mid = (r + l) / 2;
        update_h(l, mid, L, R, val, idx * 2);
        update_h(mid + 1, r, L, R, val, idx * 2 + 1);
        tree[idx] = tree[idx * 2] + tree[idx * 2 + 1];
    }
 
    ll query_h(int l, int r, int L, int R, int idx) {
        push(l, r, idx);
        if (L <= l && r <= R)
            return tree[idx];
        if (r < L || l > R)
            return 0;
        int mid = (r + l) / 2;
        ll out = query_h(l, mid, L, R, idx * 2) + query_h(mid + 1, r, L, R, idx * 2 + 1);
        tree[idx] = tree[idx * 2] + tree[idx * 2 + 1];
        return out; 
    }
 
    void update(int l, int r, int val) {
        update_h(0, n - 1, l, r, val, 1);
    }
 
    ll query(int l, int r) {
        return query_h(0, n - 1, l, r, 1);
    }
};
 
int main() {
    int n, q;
    cin >> n >> q;
 
    seggy seg(n);
    set<pair<pii, int> > cols;
    for (int i = 0; i < n; i++)
        cols.insert(mp(mp(i, i), i + 1));
    
    while (q--) {
        int t, l, r;
        cin >> t >> l >> r;
        l--, r--;
        if (t == 1) {
            int col;
            cin >> col;
            auto ite = cols.lower_bound(mp(mp(l, l), -1));
            if (ite != cols.begin())
                ite--;
            pair<pii, int> neww = pair<pii, int>(mp(l, r), col);

            vector<pair<pii, int> > toadd;
            toadd.push_back(neww);
            vector<pair<pii, int> > toremove;
            while (ite != cols.end() && ite->first.first <= r) {
                if (ite -> first.first < l) {
                    pair<pii, int> lft = mp(mp(ite -> first.first, l - 1), ite -> second);
                    toadd.push_back(lft);
                }

                if ((ite)->first.second > r) {
                    pair<pii, int> right = mp(mp(r + 1, ite -> first.second), ite -> second);
                    toadd.push_back(right);
                }

                toremove.push_back(*ite);
                seg.update(max(l, ite->first.first), min(r, ite->first.second), abs(col - ite->second));
                ite++;
            }

            for (pair<pii, int> x : toremove)
                cols.erase(x);
            for (pair<pii, int> x : toadd)
                cols.insert(x);
        }
        else {
            cout << seg.query(l, r) << "\n";
        }
    }
}