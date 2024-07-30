#include <bits/stdc++.h>
#define mp make_pair

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

struct seggy {
    vector<int> tree;
    int n;
    
    seggy(int siz, vector<int> arr) {
        n = siz;
        tree.resize(2 * n, 0);

        for (int i = n; i < 2 * n; i++)
            tree[i] = arr[i - n];
        for (int i = n - 1; i > 0; i--)
            tree[i] = max(tree[i * 2], tree[i * 2 + 1]);
    }

    int query(int l, int r) {
        int out = -1e9;
        for (l += n, r += n + 1; l < r; l /= 2, r /= 2)
        {
            if (l & 1)
                out = max(out, tree[l++]);
            if (r & 1)
                out = max(out, tree[--r]);
        }
        return out;
    }

    void mod(int idx, int val) {
        for (idx += n, tree[idx] -= val, idx /= 2; idx > 0; idx /= 2) {
            tree[idx] = max(tree[idx * 2], tree[idx * 2 + 1]);
        }
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int n, m;
    cin >> n >> m;

    vector<int> arr(n);
    for (int i = 0; i < n; i++)
        cin >> arr[i];
    seggy seg(n, arr);
    for (int i = 0; i < m; i++) {
        int curr;
        cin >> curr;
        if (seg.query(0, n - 1) < curr) {
            cout << "0 ";
            continue;
        }
        if (seg.query(0, 0) >= curr) {
            cout << "1 ";
            seg.mod(0, curr);
            continue;
        }
        int k = 0;
        for (int step = n / 2; step > 0; step /= 2) {
            while (k + step < n && seg.query(0, k + step) < curr)
                k += step;
        }
        seg.mod(k + 1, curr);
        cout << k + 2 << " ";
    }
    cout << endl;
}