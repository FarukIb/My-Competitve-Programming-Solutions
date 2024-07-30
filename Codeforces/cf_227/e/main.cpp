#include <bits/stdc++.h>
#define mp make_pair

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

struct sparse {
    vector<vector<int> > table;
    int n;
    vector<int> lg;
    sparse(vector<int> arr) {
        n = arr.size();
        lg.resize(n + 1, 0);
        lg[1] = 0;
        for (int i = 2; i <= n; i++)
            lg[i] = lg[i / 2] + 1;
        
        int k = lg[n];
        table.resize(k + 1, vector<int>(n, 1e9));
        table[0] = arr;
        for (int i = 1; i <= k; i++) {
            for (int j = 0; j + (1 << i) <= n; j++)
                table[i][j] = min(table[i - 1][j], table[i - 1][j + (1 << (i - 1))]);
        }
    }

    int query(int l, int r) {
        int len = lg[r - l + 1];
        return min(table[len][l], table[len][r - (1 << len) + 1]);
    }
};

struct  seggy
{
    vector<int> seg;
    int n;

    seggy(int _n) {
        n = _n;
        seg.resize(2 * n, 0);
    }

    int query(int l, int r) {
        int out = 0;
        for (l += n, r += n + 1; l < r; l /= 2, r /= 2) {
            if (l & 1)
                out += seg[l++];
            if (r & 1)
                out += seg[--r];
        }
        return out;
    }

    void mod(int idx, int val) {
        for (idx += n; idx > 0; idx /= 2)
            seg[idx] += val;
    }
};


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int k, n;
    cin >> n >> k;
    vector<int> og(n);
    vector<int> neww(k);

    vector<int> index(n + 1);
    for (int i = 0; i < n; i++)
    {
        cin >> og[i];
        index[og[i]] = i;
    }
    for (int j = 0; j < k; j++)
        cin >> neww[j];
    
    vector<int> edited = og;
    int pnt = 0;
    for (int i = 0; i < k; i++) {
        while (og[pnt] != neww[i])
            pnt++, edited[pnt - 1] = n + 1;
        pnt++;
    }

    while (pnt < n)
        edited[pnt] = n + 1, pnt++;
    
    sparse spar(edited);
    ll out = 0;
    seggy seg(n);
    for (int h = 1; h <= n; h++) {
        int i = index[h];
        if (edited[i] != n + 1)
            continue;
        
        int kl = i;
        for (int step = n - 1; step > 0; step /= 2)
            while (kl - step >= 0 && spar.query(kl - step, i - 1) > og[i])
                kl -= step;
        int kr = i;
        for (int step = n - 1; step > 0; step /= 2)
            while (kr + step < n && spar.query(i + 1, kr + step) > og[i])
                kr += step;
        
        out += (ll)(kr - kl + 1) - seg.query(kl, kr);
        seg.mod(i, 1);
    }

    cout << out << "\n";
}