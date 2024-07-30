#include <bits/stdc++.h>
#define mp make_pair

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

struct seggy {
    vector<pii> t;
    int n;
    int time = 0;

    void mod(int l, int r, int val) {
        pii my(time, val);
        for (l += n, r += n + 1; l < r; l /= 2, r /= 2) {
            if (l & 1)
                t[l++] = my;
            if ( r & 1)
                t[--r] = my;
        }
        time++;
    }

    seggy(vector<int>arr) {
        n = arr.size();
        t.resize(n * 2, pii(-1e9, 1e9));
        for (int i = 0; i < n; i++)
            mod(i, i, arr[i]);
    }

    int query(int idx) {
        pii out(-1e9, 1e9);
        for (idx += n; idx > 0; idx /= 2) {
            out = max(out, t[idx]);
        }
        return out.second;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int n, q;
    cin >> n >> q;

    vector<int> arr(n, 0);
    
    seggy seg(arr);
    while (q--) {
        int l;
        cin>> l;
        if (l == 0) {
            for (int i = 0; i < n; i++)
                cout << seg.query(i) <<" ";
            cout <<"\n";
        }
        else {
            int r, a;
            cin >> r >>a;
            l--, r--;
            seg.mod(l, r, a);
        }
    }
}