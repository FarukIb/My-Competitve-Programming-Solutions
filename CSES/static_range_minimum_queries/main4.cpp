#include <bits/stdc++.h>

using namespace std;

int K = 20;

struct rmq {
    vector<vector<int> > table;
    int n;
    rmq() {}
    rmq(vector<int> arr) {
        n = arr.size();
        table = vector<vector<int> > (K, vector<int>(n));
        table[0] = arr;

        for (int i = 1; i < K; i++)
            for (int j = 0; j + (1 << i - 1) < n; j++)
                table[i][j] = min(table[i - 1][j], table[i - 1][j + (1 << i - 1)]);
    }

    int query(int l, int r) {
        int po = __lg(r - l + 1);
        return min(table[po][l], table[po][r - (1 << po) + 1]);
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int n, q;
    cin >> n >> q;
    vector<int> arr(n);
    for (int i = 0; i < n; i++)
        cin >> arr[i];
    
    rmq tab(arr);
    while (q--) {
        int f, t;
        cin >> f >> t;
        cout <<tab.query(f - 1, t - 1) << "\n";
    }
}