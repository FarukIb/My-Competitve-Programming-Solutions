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
        tree.resize(n*4);
        build(0, n - 1, 1, arr);
    }
    
    void build(int l, int r, int idx, vector<int> &arr) {
        if (l == r) {
            tree[idx] = arr[l];
            return;
        }
        int mid = (l + r) / 2;
        build(l, mid, idx * 2, arr);
        build(mid + 1 , r, idx*2+1, arr);
        tree[idx] = max(tree[idx*2], tree[idx*2+1]);
    }

    int query(int l, int r, int idx, int target) {
        if (l == r) {
            tree[idx] -= target;
            return l;
        }
        int mid = (l + r) / 2; int ans;
        if (tree[idx*2] >= target)
            ans = query(l, mid, idx*2, target);
        else
            ans = query(mid + 1, r, idx*2+1, target);
        tree[idx] = max(tree[idx*2], tree[idx*2+1]);
        return ans;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int n, m;
    cin >> n >> m;
    vector<int>arr(n);
    for (int i = 0; i < n; i++)
        cin >> arr[i];
    seggy seg(arr);
    while (m--) {
        int v;
        cin >> v;
        if (seg.tree[1] < v)
            cout <<"0 ";
        else
            cout << seg.query(0, n - 1, 1, v) + 1 << " ";
    }
}