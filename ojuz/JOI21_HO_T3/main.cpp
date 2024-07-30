#include <bits/stdc++.h>
#define mp make_pair
#define all(a) a.begin(), a.end()

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

struct seggy {
    vector<int> t;
    int n;

    seggy(int siz) {n = siz, t.resize(n*2);}

    int query(int l, int r) {
        int out = 0;
        for (l += n, r += n + 1; l < r; l /= 2, r /= 2) {
            if (l & 1)
                out += t[l++];
            if (r & 1)
                out += t[--r];
        }
        return out;
    }

    void mod(int idx) {
        for (idx += n; idx > 0; idx /= 2)
            t[idx]++;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int n;
    cin >> n;
    vector<int> perm(n);
    for (int i = 0; i < n; i++) {
        cin >> perm[i];
        perm[i]--;
    }

    seggy idxseg(n);
    for (int i = 0; i < n; i++) {
        
    }
}