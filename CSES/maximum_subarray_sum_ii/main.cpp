#include <bits/stdc++.h>
#define mp make_pair
#define all(a) a.begin(), a.end()

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

struct seggy {
    vector<ll> tree;
    int n;

    seggy(vector<ll> arr) {
        n = arr.size();
        tree.resize(2*n);
        for (int i = 0; i < n; i++)
            tree[i + n] = arr[i];
        for (int i = n - 1; i > 0; i--)
            tree[i] = max(tree[i*2], tree[i*2+1]);
    }

    ll query(int l, int r) {
        ll maxi = -1e18;
        for (l += n, r += n + 1; l < r; l/= 2, r /= 2) {
            if (l & 1)
                maxi = max(maxi, tree[l++]);
            if (r & 1)
                maxi = max(maxi, tree[--r]);
        }
        return maxi;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int n, a, b;
    cin >> n >> a >> b;
    vector<ll> arr(n+1);
    vector<ll> cumsum(n+1);
    for (int i = 1; i <= n; i++)
    {
        cin >> arr[i];
        cumsum[i] = arr[i] + cumsum[i - 1];
    }

    seggy seg(cumsum); ll out = -1e18;
    for (int i = 0; i <= n; i++)
        out = max(out, seg.query(i+a,min(n, i+b))-cumsum[i]);
    cout << out << endl;
}