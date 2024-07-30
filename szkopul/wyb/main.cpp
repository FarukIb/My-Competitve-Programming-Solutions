#include <bits/stdc++.h>
#define mp make_pair
#define all(a) a.begin(), a.end()

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

struct upd {
    int c[5];
    upd() {}
    upd(bool isup) {
        if (isup)
            c[0] = 0, c[1] = 1, c[2] = 2, c[3] = 3, c[4] = 4;
        else
            c[0] = c[1] = c[2] = c[3] = c[4] = 0;
    }

    bool operator==(const upd& b) const {return c[0] == b.c[0] and c[1] == b.c[1] and c[2] == b.c[2] and c[3] == b.c[3] and c[4] == b.c[4]; }
};

upd def(true);

upd merge_upd(upd &a, upd b) {
    for (int i = 0; i < 5; i++)
        b.c[i] = a.c[b.c[i]];
    return b;
}

upd merge_node(upd a, upd b) {
    for (int i = 0; i < 5; i++)
        b.c[i] += a.c[i];
    return b;
}

upd apply_upd(upd &up, upd &nod) {
    upd newnn(false);
    for (int i = 0; i < 5; i++)
        newnn.c[up.c[i]] += nod.c[i];
    return newnn;
}

struct seggy {
    vector<upd> tree;
    vector<upd> lazy;
    int n;
    string s;

    seggy(vector<int> arr) {
        n = arr.size();
        tree.resize(n*4, upd(false));
        lazy.resize(n*4, def);
        build(0, n - 1, 1, arr);
        s = string(n, '0');
    }

    void build(int l, int r, int idx, vector<int> &arr) {
        if (l == r)
        {
            tree[idx].c[arr[l]]++;
            return;
        }
        int mid = (l + r) / 2;
        build(l, mid, idx*2, arr);
        build(mid + 1, r, idx*2+1, arr);
        tree[idx] = merge_node(tree[idx*2], tree[idx*2+1]);
    }

    void push(int idx, int l, int r) {
        if (lazy[idx] == def)
            return;
        tree[idx] = apply_upd(lazy[idx], tree[idx]);
        if (l != r)
            lazy[idx * 2] = merge_upd(lazy[idx], lazy[idx * 2]), lazy[idx * 2 + 1] = merge_upd(lazy[idx], lazy[idx * 2 + 1]);
        lazy[idx]  = def;
    }

    void reconstruct(int l, int r, int idx) {
        push(idx, l, r);
        if (l == r) {
            for (int i = 0; i < 5; i++)
                if (tree[idx].c[i] == 1)
                    s[l] = i + 'a';
            return;
        }
        int mid = (l + r) / 2;
        reconstruct(l, mid, idx*2);
        reconstruct(mid + 1, r, idx*2+1);
    }

    void apply(int l, int r, int idx, int &col, int left, upd &updat) {
        if (idx == 1)
            push(idx, l, r);
        if (left == 0)
            return;
        
        int mid = (l + r) / 2;
        if (l != r)
        {
            push(idx * 2, l, mid);
            push(idx * 2 + 1, mid + 1, r);
        }
        int lval = tree[idx*2].c[col], rval = tree[idx*2+1].c[col];
        if (lval + rval == left) {
            lazy[idx] = merge_upd(updat, lazy[idx]);
            push(idx, l, r);
            return;
        }
        else if (lval <= left) {
            lazy[idx*2] = merge_upd(updat, lazy[idx*2]);
            push(idx * 2, l, mid);
            apply(mid + 1, r, idx*2+1, col, left - lval, updat);
        } else {
            apply(l, mid, idx*2, col, left, updat);
        }
        if (l != r)
            tree[idx] = merge_node(tree[idx*2], tree[idx*2+1]);
    }   
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int n, m;
    cin >> n >> m;
    if (n <= 10) {
        string s;
        cin >> s;
        while (m--) {
            int cnt; char a, b;
            cin >> cnt >> a >> b;
            for (int i = 0; i < n and cnt > 0; i++) 
                cnt = s[i] == a ? cnt - 1 : cnt, s[i] = s[i] == a ? b : s[i];
        }
        cout << s << "\n";
        return 0;
    }
    string s;
    cin >> s;
    vector<int> arr(n);
    for (int i = 0; i < n; i++)
        arr[i] = s[i] - 'a';
    seggy seg(arr);
    
    while (m--) {
        int x; char a, b;
        cin >>x >> a >> b;
        a -= 'a', b -= 'a';
        int inta = (int)a;
        upd myupd(true);
        myupd.c[(int)a] = (int)b;
        seg.apply(0, n - 1, 1, inta, x, myupd);
    }

    seg.reconstruct(0, n - 1, 1);
    cout << seg.s << "\n";
}