#include <bits/stdc++.h>
#define pii pair<int, int>
#define ll long long
#define ld long double

using namespace std;

struct seggy {
    vector<int> tree;
    int n;
    
    seggy(vector<int> arr) {
        n = arr.size();
        tree.resize(n * 2);
        for (int i = n; i < 2 * n; i++)
            tree[i] = arr[i - n];
        for (int i = n - 1; i > 0; i--)
            tree[i] = min(tree[i * 2], tree[i * 2 + 1]);
    }

    int query(int l, int r) {
        int out = 2e9;
        for (l += n, r += n + 1; l < r; l /= 2, r /= 2) {
            if (l & 1)
                out = min(out, tree[l++]);
            if (r & 1)
                out = min(out, tree[--r]);
        }
        return out;
    }

    int update(int idx, int val) {
        for (idx += n, tree[idx] = val, idx /= 2; idx > 0; idx /= 2)
            tree[idx] = min(tree[idx * 2], tree[idx * 2 + 1]);
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int n, q;
    cin >> n >> q;
    vector<int> arr(n);
    vector<int> fleft(n);
    vector<int> fright(n);
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
        fleft[i] = fright[i] = arr[i];

        fleft[i] += i, fright[i] += n - i - 1;
    }

    seggy l(fleft), r(fright);

    while (q--) {
        int tip;
        cin >> tip;
        if (tip == 1) {
            int idx, val;
            cin >> idx >> val;
            idx -= 1;
            l.update(idx, val + idx);
            r.update(idx, val + n - idx - 1);
        }
        else {
            int idx;
            cin >> idx;
            idx--;
            cout << min(l.query(idx, n - 1) - idx, r.query(0, idx) - (n - idx - 1)) << "\n";
        }
    }
}
