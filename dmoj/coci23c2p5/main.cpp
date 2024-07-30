#include <bits/stdc++.h>
#define mp make_pair
#define all(a) a.begin(), a.end()

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

struct query {
    int add;
    int h, l, r, idx;
    query() {}

    query(int L, int R, int idxx, int H) {
        add = 0;
        l = L, r = R, idx = idxx, h = H;
    }

    query(int H, int idxx) {
        add = 1;
        idx = idxx, h = H;
    }

    bool operator<(const query& b) const {
        if (h == b.h)
            return add < b.add;
        return h > b.h;
    }
};

struct seggy {
    int n;
    vector<int> tree;
    
    seggy() {}
    seggy(int N) {
        n = N;
        tree = vector<int> (2 * n);
    }

    void mod(int idx, int val) {
        for (idx += n; idx > 0; idx /= 2)
            tree[idx] += val;
    }

    int query(int l, int r) {
        int out = 0;
        for (l += n, r += n + 1; l < r; l/= 2, r/= 2)
        {
            if (l & 1)
                out += tree[l++];
            if (r & 1)
                out += tree[--r];
        }
        return out;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int n, q;
    cin >> n >> q;
    vector<query> queries(n + q);
    for (int i = 0; i < n; i++) {
        int h;
        cin >> h;
        queries[i] = query(h, i + 1);
    }
    vector<int> ans(q);
    for (int i = 0; i < q; i++) {
        int l, r, x;
        cin >> l >> r >> x;
        queries[i + n] = query(l, r, i, x);
    }
    sort(all(queries));
    seggy seg(n + 1);
    vector<bool> erect(n + 2);
    vector<int> vals(n + 2);
    for (query q : queries) {
        if (q.add) {
            erect[q.idx] = true;
            if (vals[q.idx + 1])
            {
                vals[q.idx + 1] = 0;
                seg.mod(q.idx + 1, -1);
            }
            if (!erect[q.idx - 1]) {
                vals[q.idx] = 1;
                seg.mod(q.idx, 1);
            }
        } else {
            int an = seg.query(q.l + 1, q.r);
            if (erect[q.l])
                an++;
            ans[q.idx] = an;
        }
    }

    for (int a : ans)
        cout << a << "\n";
}