#include <bits/stdc++.h>
#define mp make_pair
#define all(a) a.begin(), a.end()

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

struct seggy {
    vector<int> tree;
    int n;

    seggy(vector<int> arr) {
        n = arr.size();
        tree.resize(4*n);
        build(0, n - 1, 1, arr);
    }

    void build(int l, int r, int idx, vector<int> &arr) {
        if (l == r) {
            tree[idx] = arr[l];
            return;
        }
        int mid = (l + r) / 2;
        build(l, mid, idx*2, arr);
        build(mid + 1, r, idx*2+1, arr);
        tree[idx] = min(tree[idx*2], tree[idx*2+1]);
    }

    int query(int l, int r, int L, int R, int idx) {
        if (l > R || r < L)
            return 1e9;
        if (l >= L and r <= R)
            return tree[idx];
        int mid = (l + r) / 2;
        return min(query(l, mid, L, R, idx*2), query(mid + 1, r, L, R, idx*2+1));
    }

    int query(int l, int r) {
        return query(0, n - 1, l, r, 1);
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int n, q;
    cin >> n >>q;
    vector<int> arr(n);
    for (int i = 0; i < n; i++)
        cin >>arr[i];
    seggy seg(arr);
    while (q--) {
        int l, r;
        cin >> l >> r;
        l--, r--;
        cout << seg.query(l, r) << "\n";
    }
}