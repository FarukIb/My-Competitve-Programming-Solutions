#include <bits/stdc++.h>

using namespace std;

struct seggy {
    int n;
    vector<int> tree;

    seggy(int siz) {
        n = siz;
        tree.resize(2 * n, 0);
    }

    void update(int l, int r) {
        for (l += n, r += n + 1; l < r; l /= 2, r /= 2) {
            if (l & 1)
                tree[l++]++;
            if (r & 1)
                tree[--r]++;
        }
    }

    int query(int idx) {
        int out = 0;
        for (idx += n; idx > 0; idx /= 2)
            out += tree[idx];
        return out;
    }
};

int main() {
    int n;
    cin >> n;
    vector<int> arr(n);
    for (int i = 0; i < n; i++)
        cin >> arr[i];
    seggy seg(n);
    
    vector<int> out;
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        x--;

        // BIN SEARCH
        int k = 0;
        for (int b = n / 2; b >= 1; b /= 2) {
            while (k + b < n && k + b - seg.query(k + b) <= x)
                k += b;
        }

        out.push_back(arr[k]);
        seg.update(k, n - 1);
    }

    for (int i = 0; i < n; i++)
        cout << out[i] <<" ";
    cout << endl;
}