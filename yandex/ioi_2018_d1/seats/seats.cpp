#include "seats.h"
#include <bits/stdc++.h>
#pragma GCC target ("avx2")
#pragma GCC optimization ("O3")
#pragma GCC optimization ("unroll-loops")

using namespace std;

struct node {
    int maxi, mini, maxj, minj;
};

node merge(node a, node b) {
    return {max(a.maxi, b.maxi), min(a.mini, b.mini), max(a.maxj, b.maxj), min(b.minj, a.minj)};
}

struct seggy {
    vector<node> tree;
    int n;
    seggy() {}
    seggy(vector<int> r, vector<int> c) {
        n = r.size();

        tree.resize(n*2);
        for (int i = n; i < 2 * n; i++)
            tree[i] = {r[i - n], r[i - n], c[i - n], c[i - n]};
        
        for (int i = n - 1; i > 0 ; i--)
            tree[i] = merge(tree[i*2], tree[i*2+1]);
    }

    void sett(node val, int idx) {
        for (idx += n, tree[idx] = val, idx /= 2; idx > 0; idx /= 2)
            tree[idx] = merge(tree[idx*2], tree[idx*2+1]);
    }

    node query(int l, int r) {
        node val = {(int)-1e9, (int)1e9, (int)-1e9, (int)1e9};
        for (l += n, r += n + 1; l < r; l /= 2, r /= 2) {
            if (l & 1)
                val = merge(val, tree[l++]);
            if (r & 1)
                val = merge(val, tree[--r]);
        }
        return val;
    }
};

seggy seg;

vector<int> r;
vector<int> c;

void give_initial_chart(int H, int W, std::vector<int> R, std::vector<int> C) {
    r = R;
    c = C;
    seg = seggy(r, c);
}

int swap_seats(int a, int b) {
    if (a > b)
        swap(a, b);
    swap(r[a], r[b]);
    swap(c[a], c[b]);

    seg.sett({r[a], r[a], c[a], c[a]}, a);
    seg.sett({r[b], r[b], c[b], c[b]}, b);

    int ans = 0;
    for (int i = 0; i < r.size();) {
        node q = seg.query(0, i);

        int area = (q.maxi - q.mini + 1) * (q.maxj - q.minj + 1);
        if (i == area - 1) {
            ans++;
            i++;
        } else {
            i = area - 1;
        }
    }

    return ans;
}
