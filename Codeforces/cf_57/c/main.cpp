#include <bits/stdc++.h>
#define mp make_pair

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

struct seggy {
    int n;
    vector<int> tree;

    seggy(int N) {
        n = N;
        tree.resize(n * 2, 0);
    }

    ll query(int l, int r) {
        int out = 0;
        for (l += n, r += n + 1; l < r; l /= 2, r /= 2) {
            if (l & 1)
                out += tree[l++];
            if (r & 1)
                out += tree[--r];
        }
        return out;
    }

    void mod(int idx, int val) {
        idx += n;
        for (;idx > 0; idx /= 2)
            tree[idx] += val;
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
    vector<int> arr2 = arr;
    sort(arr2.begin(), arr2.end());
    map<int, int> mapp;
    int curr = 1;
    mapp[arr2[0]] = 0;
    for (int i = 1; i < n; i++) {
        if (arr2[i] != arr2[i - 1]) {
            mapp[arr2[i]] = curr;
            curr++;
        }
    }
    seggy segr(n);
    seggy segl(n);
    for (int i = 0; i < n; i++)
    {
        arr[i] = mapp[arr[i]];
        if (i > 0)
            segr.mod(arr[i], 1);
    }
    segl.mod(arr[0], 1);
    ll out = 0;
    for (int i = 1; i < n - 1; i++) {
        segr.mod(arr[i], -1);
        out += segl.query(arr[i] + 1, n - 1) * segr.query(0, arr[i] - 1);
        segl.mod(arr[i], 1);
    }

    cout << out << "\n";
}