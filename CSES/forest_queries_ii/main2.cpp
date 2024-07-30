#include <bits/stdc++.h>
#define mp make_pair
#define all(a) a.begin(), a.end()

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

vector<string> mat;

int n;
struct seggy {
    vector<int> tree;
    seggy() {}
    seggy(int row) {
        tree.resize(n*4, 0);
        build(0, n - 1, 1, row);
    }

    void build(int l, int r, int idx, int row) {
        if (l == r) {
            tree[idx] = mat[row][l] == '*' ? 1 : 0;
            return;
        }
        int mid = (l + r) / 2;
        build(l, mid, idx*2, row);
        build(mid + 1, r, idx*2+1, row);
        tree[idx] = tree[idx*2] + tree[idx * 2 + 1];
    }

    void upd(int l, int r, int T, int val, int idx) {
        tree[idx] += val;
        if (l == r) 
            return;
        int mid = (l + r) / 2;
        if (T <= mid)
            upd(l, mid, T, val, idx*2);
        else
            upd(mid + 1, r, T, val, idx*2+1);
    }

    int query(int l, int r, int L, int R, int idx) {
        if (l > R || r < L)
            return 0;
        if (l >= L and r <= R)
            return tree[idx];
        int mid = (l + r) / 2;
        return query(l, mid, L, R, idx*2) + query(mid + 1, r, L, R, idx*2+1);
    }
};

void merge_seg(seggy &seg1, seggy &seg2, seggy &endseg) {
    for (int i = 0; i < 4*n; i++)
        endseg.tree[i] = seg1.tree[i] + seg2.tree[i];
}

struct seg2d {
    vector<seggy> tree;
    
    seg2d() {
        tree.resize(4*n);
        build(0, n - 1, 1);
    }

    void build(int l, int r, int idx) {
        if (l == r) {
            tree[idx] = seggy(l);
            return;
        }
        int mid = (l + r) / 2;
        build(l, mid, idx*2);
        build(mid + 1, r, idx*2+1);
        tree[idx].tree = vector<int>(4*n, 0);
        merge_seg(tree[idx*2], tree[idx*2+1], tree[idx]);
    }

    void upd(int l, int r, int idx, int y, int x, int val) {
        tree[idx].upd(0, n - 1, x, val, 1);
        if (l == r)
            return;
        int mid = (l + r) / 2;
        if (y <= mid)
            upd(l, mid, idx*2, y, x, val);
        else
            upd(mid + 1, r, idx*2+1, y, x, val);
    }

    int query(int l, int r, int idx, int y1, int x1, int y2, int x2) {
        if (l > y2 || r < y1)
            return 0;
        if (l >= y1 and r <= y2)
            return tree[idx].query(0, n - 1, x1, x2, 1);
        int mid = (l + r) / 2;
        return query(l, mid, idx * 2, y1, x1, y2, x2) + query(mid + 1, r, idx*2+1, y1, x1, y2, x2);
    }
};

void brute(int y1, int x1, int y2, int x2) {
    int out = 0;
    for (int i = y1; i <= y2; i++)
        for (int j = x1; j <= x2; j++)
            out += mat[i][j] == '*' ? 1 : 0;
    cout << out << " ";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int q;
    cin >> n >> q;
    mat = vector<string>(n);
    for (int i = 0; i < n; i++)
        cin >> mat[i];
    seg2d seggy;
    while (q--) {
        int t;
        cin >> t;
        if (t == 1) {
            int x, y;
            cin >> y >> x;
            x--, y--;
            int val = -1;
            if (mat[y][x] == '.')
                val = 1, mat[y][x] = '*';
            else
                mat[y][x] = '.';
            seggy.upd(0, n - 1, 1, y, x, val);
        } else {
            int y1, x1, y2, x2;
            cin >> y1 >> x1 >> y2 >> x2;
            y1--, x1--, y2--, x2--;
            //brute(y1, x1, y2, x2);
            cout << seggy.query(0, n - 1, 1, y1, x1, y2, x2) << "\n";
        }
    }
}