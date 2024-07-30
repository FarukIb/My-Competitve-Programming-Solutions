#include <bits/stdc++.h>
#define mp make_pair
#define all(a) a.begin(), a.end()

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

const int K = 20;

struct sparse {
    vector<vector<int> > sp;
    vector<int> lg;
    int n;
    sparse(vector<int> arr) {
        n = arr.size();
        lg.resize(n + 1);
        for (int i = 2; i <= n; i++)
            lg[i] = lg[id / 2] + 1;
        sp.resize(K, vector<int>(n+1));
        sp[0] = arr;
        for (int i = 1; i < K; i++)
            for (int j = 0; j + (1 << (i - 1)) < n; j++) 
                sp[i][j] = min(sp[i - 1][j], sp[i - 1][j + (1 << (i - 1))]);
    }

    int query(int l, int r) {
        int i = lg[r - l + 1];
        return min(sp[i][l], sp[i][r - (1 << i) + 1]);
    }  
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int n, q;
    cin >> n >> q;
    vector<int> arr(n);
    for (int i = 0; i < n; i++)
        cin >>arr[i];
    sparse sp(arr);
    while (q--) {
        int l, r;
        cin >>l >>r;
        cout << sp.query(l - 1,r - 1) << "\n";
    }
}