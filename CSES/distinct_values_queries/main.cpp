#include <bits/stdc++.h>
#define pii pair<int, int>
#define ll long long
#define ld long double

using namespace std;

struct bit {
    vector<int> tree;
    int n;
    
    bit(int _size) {
        n = _size;
        tree.resize(_size + 1, 0);
    }

    int query(int idx) {
        int sum = 0;
        while (idx > 0)
            sum += tree[idx], idx -= idx & (-idx);
        return sum;
    }

    void upd(int idx, int val) {
        while (idx <= n)
            tree[idx] += val, idx += idx & (-idx);
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int n, q;
    cin >> n >> q;

    vector<int> arr(n);
    for (int i =0 ; i < n; i++)
        cin >> arr[i];
    bit BIT(n);

    vector<vector<pii> > queries(n + 1);
    for (int i = 0; i < q; i++) {
        int f, t;
        cin >> f >> t;
        queries[f].push_back(pii(t, i));
    }

    map<int, int> first;
    vector<int> out(q);
    for (int i = n; i > 0; i--) {
        int curr = arr[i - 1];
        if (first.count(curr))
            BIT.upd(first[curr], -1);
        first[curr] = i;
        BIT.upd(i, 1);
        for (auto x : queries[i])
            out[x.second] = BIT.query(x.first);
    }

    for (int i = 0; i< q; i++)
        cout << out[i] << "\n";
}
