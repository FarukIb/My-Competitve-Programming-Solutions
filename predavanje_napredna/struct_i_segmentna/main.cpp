#include <bits/stdc++.h>

using namespace std;

struct seggy {
    vector<int> tree;
    int n;

    void build(vector<int> arr) 
    {
        n = arr.size();
        tree.resize(2 * n);
        for (int i = n; i < 2 * n; i++)
            tree[i] = arr[i - n];
        for (int i = n - 1; i > 0; i--)
            tree[i] = tree[i* 2] + tree[i * 2 + 1];
    }

    int query(int l, int r) {
        int sum = 0;
        for (l += n, r += n + 1; l < r; l /= 2, r /= 2) {
            if (l % 2 == 1)
                sum += tree[l++];
            if (r % 2 == 1)
                sum += tree[--r];
        }
        return sum;
    }

    void modify(int idx, int new_val) {
        idx += n;
        for (tree[idx] = new_val, idx /= 2; idx > 0; idx /= 2)
            tree[idx] = tree[idx * 2] + tree[idx * 2 + 1];
    }
};

int main() {
    
}