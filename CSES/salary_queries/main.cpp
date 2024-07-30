#include <bits/stdc++.h>
#define pii pair<int, int>
#define ll long long
#define ld long double

using namespace std;

struct query {
    char type;
    int f, s;
    query(char _type, int _f, int _s) {
        type = _type, f = _f, s = _s;
    }
    query() {}
};

map<int, int> compress;

struct seggy { 
    vector<int> tree;
    int n;

    seggy(int _size) {
        n = _size;
        tree.resize(n * 2, 0);
    }

    void update(int idx, int val) {
        for (idx += n; idx > 0; idx /= 2)
            tree[idx] += val;
    }

    int query(int l, int r) {
        int sum = 0;
        for (l += n, r += n + 1; l < r; l /= 2, r /= 2) {
            if (l & 1)
                sum += tree[l++];
            if (r & 1)
                sum += tree[--r];
        }
        return sum;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int n, q;
    cin >> n >> q;
    vector<int> arr(n);
    vector<query> queries(q);
    
    vector<int> all;
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
        all.push_back(arr[i]);
    }

    for (int i = 0; i < q; i++) {
        query neww;
        cin >> neww.type >> neww.f >> neww.s;
        queries[i] = neww;
        if (neww.type == '?')
            all.push_back(neww.f);
        all.push_back(neww.s);
    }


    seggy seg(all.size() + 1);
    int cnt = 0;
    sort(all.begin(), all.end());
    for (int i = 0; i < all.size(); i++)
        if (i == 0 || all[i] != all[i - 1])
            compress[all[i]] = cnt++;

    
    for (int i = 0; i < n; i++)
        arr[i] = compress[arr[i]], seg.update(arr[i], 1);
    
    for (query s : queries) {
        if (s.type == '?')
            s.f = compress[s.f];
        s.s = compress[s.s];

        if (s.type == '?') {
            cout << seg.query(s.f, s.s) << "\n";
        }
        else
            seg.update(arr[s.f - 1], -1), seg.update(s.s, 1), arr[s.f - 1] = s.s;
    }
}
