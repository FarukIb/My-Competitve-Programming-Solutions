#include <bits/stdc++.h>
#define mp make_pair

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

struct seggy {
    vector<int> tree;
    vector<int> vals;
    int n;

    seggy(vector<int> arr) {
        n = arr.size();

        tree.resize(n * 4, 0);
        vals.resize(n * 4, 0);

        build(1, 0, n - 1, arr);
    }

    void build(int idx, int l, int r, vector<int> &arr) {
        tree[idx] = r - l + 1;
        if (l == r) {
            vals[idx] = arr[l];
            return;
        }

        int mid = (r + l) / 2;
        build(idx * 2, l, mid, arr);
        build(idx * 2 + 1, mid + 1, r, arr);
    }

    void update(int idx, int pnt, int l, int r) {
        tree[idx]--;
        if (l == r)
            return;
        int mid = (r + l) / 2;
        if (pnt >= l && pnt <= mid)
            update(idx * 2, pnt, l, mid);
        else
            update(idx * 2 + 1, pnt, mid + 1, r);
    }

    pii walk(int val, int l, int r, int idx) {
        if (l == r)
            return mp(l, vals[idx]);
        
        int left = tree[idx * 2], right = tree[idx * 2 + 1];
        int mid = (r + l) / 2;
        if (left >= val)
            return walk(val, l, mid, idx * 2);
        return walk(val - left, mid + 1, r, idx * 2 + 1);
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int n;
    cin >> n;
    vector<int> arr(n);
    for (int i = 0; i < n; i++)
        cin >> arr[i];
    
    seggy seg(arr);
    vector<int> out;
    for (int i = 0; i < n; i++) {
        int idx;
        cin >> idx;

        pii myidx = seg.walk(idx, 0, n - 1, 1);
        out.push_back(myidx.second);
        seg.update(1, myidx.first, 0, n - 1);
    }

    for (int x : out)
        cout << x << " ";
    cout << "\n";
}