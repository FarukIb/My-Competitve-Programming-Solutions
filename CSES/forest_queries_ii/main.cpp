#include <bits/stdc++.h>
#include <variant>
#define mp make_pair

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

void flip(int &s) {
    s = s == 0 ? 1 : 0;
}

struct seggy {
    vector<int> tree;
    int n;

    seggy() {n = 0;}

    seggy(string s) {
        n = s.size();
        tree.resize(n * 2, 0);
        for (int i = 0; i < n; i++)
            tree[i + n] = s[i] == '.' ? 0 : 1;
        for (int i = n - 1; i > 0; i--) 
            tree[i] = tree[i * 2] + tree[i * 2 + 1];
    }

    void update(int idx, int val) {
        for (idx += n, tree[idx] += val, idx /= 2; idx > 0; idx /= 2)
            tree[idx] += val;
    }

    int query(int l, int r) {
        int out = 0;
        for (l += n, r += n + 1; l < r; l /= 2, r /= 2) {
            if (l & 1)
                out += tree[l++];
            if (r & 1)
                out += tree[--r];
        }
        return out;
    }
};

struct seggy2 {
    vector<seggy> tree;
    vector<string> mat;
    int n;

    seggy2(vector<string> s) {
        mat = s;
        n = s.size();
        tree.resize(n * 2);
        for (int i = 0; i < n; i++)
            tree[i + n] = seggy(s[i]);
        for (int i = n - 1; i > 0; i--) 
        {
            seggy curr(s[i]);
            for (int j = 0; j < 2 * n; j++)
                curr.tree[j] = tree[i * 2].tree[j] + tree[i * 2 + 1].tree[j];
            tree[i] = curr;
        }
    }

    void update(int idx, int idx2) {
        int val;
        if (mat[idx][idx2] == '.')
            val = 1, mat[idx][idx2] = '*';
        else
            val = -1, mat[idx][idx2] = '.';
        for (idx += n, tree[idx].update(idx2, val), idx /= 2; idx > 0; idx /= 2)
            tree[idx].update(idx2, val);
    }

    int query(int l, int l1, int r, int r1) {
        int out = 0;
        for (l += n, r += n + 1; l < r; l /= 2, r /= 2) {
            if (l & 1)
                out += tree[l++].query(l1, r1);
            if (r & 1)
                out += tree[--r].query(l1, r1);
        }
        return out;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    unordered_set<int> opp;

    int n, q;
    cin >> n >> q;
    vector<string> mat(n);
    for (int i =0 ; i < n; i++)
        cin >> mat[i];
    seggy2 seg(mat);
    while (q--) {
        int type;
        cin >> type;
        if (type == 1) {
            int x, y;
            cin >> x >> y;
            x--, y--;
            seg.update(x, y);
        }
        else {
            int x, y, x1, y1;
            cin >>x >> y >>x1 >>y1;
            x--, y--, x1--, y1--;
            cout << seg.query(x, y, x1, y1) << "\n";
        }
    }
}