#include <bits/stdc++.h>
#define mp make_pair

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

struct seggy {
    vector<int> tree;
    int n;

    seggy(vector<int> arr) {
        n = arr.size();

        tree.resize(2 * n, 0);
        for (int i = n; i < 2 * n; i++)
            tree[i] = arr[i - n];
        for (int i = n - 1; i > 0; i--)
            tree[i] = min(tree[i * 2], tree[i * 2 + 1]);
    }

    int query(int l, int r) {
        int out = 1e9;
        for (l += n, r += n + 1; l < r; l /= 2, r /= 2) {
            if (l & 1)
                out = min(out, tree[l++]);
            if (r & 1)
                out = min(out, tree[--r]);
        }
        return out;
    }

    void mod(int idx, int val) {
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
    for (int i = 0; i < n; i++)
        cin >> arr[i];

    seggy seg(arr);
    while (q--) {
        int t, a, b;
        cin >> t >> a >> b;
        if (t == 1)
            seg.mod(a - 1, b);
        else
            cout << seg.query(a - 1, b - 1) << "\n";
    }
}