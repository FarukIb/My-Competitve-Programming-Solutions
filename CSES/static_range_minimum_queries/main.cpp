#include <bits/stdc++.h>
#define mp make_pair
#define all(a) a.begin(), a.end()

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

const int K = 20;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int n, q;
    cin >> n >> q;
    vector<vector<int> > sparse(n, vector<int>(K));
    for (int i = 0; i < n; i++)
        cin >> sparse[i][0];

    vector<int> lg(n + 1);
    for (int i = 2; i <= n; i++)
        lg[i] = lg[i / 2] + 1;
    for (int j = 1; j < K; j++)
        for (int i = 0; i + (1 << (j - 1)) < n; i++)
            sparse[i][j] = min(sparse[i][j - 1], sparse[i + (1 << (j - 1))][j - 1]);
    
    while (q--) {
        int l, r;
        cin >> l >> r;
        l--,r--;
        int siz = lg[r - l + 1];
        cout << min(sparse[l][siz], sparse[r - (1 << siz) + 1][siz]) << "\n";
    }
}