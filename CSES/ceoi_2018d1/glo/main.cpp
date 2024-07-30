#include <bits/stdc++.h>
#define mp make_pair
#define all(a) a.begin(), a.end()

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

struct seggy {
    int n;
    vector<int> tree;

    seggy(int siz) {
        n = siz;
        tree.resize(n*2);
    }

    int query(int l, int r) {
        int mx = 0;
        for (l += n, r += n + 1; l < r; l /= 2, r /= 2) {
            if (l & 1)
                mx = max(mx, tree[l++]);
            if (r & 1)
                mx = max(mx, tree[--r]);
        }
        return mx;
    }

    void mod(int idx, int val) {
        for (idx += n; idx > 0; idx /= 2)
            tree[idx] = max(tree[idx], val);
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int n, x;
    cin >> n >> x;
    vector<int> arr(n); 
    for (int i = 0; i < n; i++)
        cin >> arr[i];
    vector<int> all_ele = arr;
    all_ele.push_back(0);
    all_ele.push_back(2e9);
    sort(all(all_ele));
    all_ele.erase(unique(all(all_ele)), all_ele.end());
    map<int, int> conv;
    for (int i = 0; i < all_ele.size(); i++)
        conv[all_ele[i]] = i;
    for (int i = 0; i < n; i++)
        arr[i] = conv[arr[i]];
    
    vector<int> highest_idx(all_ele.size());
    for (int i = 0; i < all_ele.size(); i++)
        highest_idx[i] = upper_bound(all(all_ele), all_ele[i] + x - 1) - all_ele.begin() - 1;
    
    vector<int> revlis(n);
    seggy myseg(all_ele.size());
    for (int i = n - 1; i >= 0; i--) {
        int possible = 1 + myseg.query(arr[i] + 1, all_ele.size() - 1);
        myseg.mod(arr[i], possible);
        revlis[i] = myseg.tree[arr[i] + myseg.n];
    }
    int out = *max_element(all(revlis));

    myseg = seggy(all_ele.size());
    for (int i = 0; i < n - 1; i++) {
        int possible = 1 + myseg.query(0, arr[i] - 1);
        myseg.mod(arr[i], possible);

        out = max(out, revlis[i + 1] + myseg.query(0, highest_idx[arr[i + 1]]));
    }

    cout << out << "\n";
}