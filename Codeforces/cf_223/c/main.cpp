#include <bits/stdc++.h>
 
using namespace std;
 
struct node {
    int maxi;
    int op, close;
    bool null = false;
    node() {maxi = 0, null = true;}
    node(bool nulll) {null = nulll;}
    node(char s) {
        if (s == '(')
            op = 1, maxi = 0, close = 0, null = false;
        else
            op = 0, maxi = 0, close = 1, null = false;
    }
};

node merge(node a, node b) {
    if (a.null)
        return b;
    if (b.null)
        return a;
    node neww(false);
    neww.maxi = a.maxi + b.maxi + min(a.op, b.close)*2;
    neww.op = a.op + b.op - min(a.op, b.close);
    neww.close = a.close + b.close - min(a.op, b.close);
    return neww;
}

struct seggy {
    vector<node> t;
    int n;
    seggy(string s) {
        n = s.size();
        t.resize(2 * n);
        for (int i = 0; i < n; i++)
            t[i + n] = node(s[i]);
        for (int i = n - 1; i > 0; i--)
            t[i] = merge(t[i * 2], t[i * 2 + 1]);
    }  

    node query(int l, int r) {
        node lmax, rmax;
        for (l += n, r += n + 1; l < r; l /= 2, r /= 2)
        {
            if (l & 1)
                lmax = merge(lmax, t[l++]);
            if (r & 1)
                rmax = merge(t[--r], rmax);
        }
        return merge(lmax, rmax);
    }
};
 
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int n;
    string s;
    cin >> s;
    n = s.size();
    seggy seg(s);

    int q;
    cin >> q;
    while (q--) {
        int l, r;
        cin >> l >>r;
        l--, r--;
        cout << seg.query(l, r).maxi << "\n";
    }
}