#include <bits/stdc++.h>
#define mp make_pair

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

struct seggy {
    vector<int> t;
    int n;

    seggy(int _size, vector<int> a) {
        n = _size;
        t.resize(n * 2, 0);
        for (int i = n; i < 2 * n; i++)
            t[i] = a[i - n];
        for (int i = n - 1; i > 0; i--)
            t[i] = min(t[i * 2], t[i * 2 + 1]);
    }

    void mod(int idx, int val) {
        for (idx += n, t[idx] += val, idx /= 2; idx > 0; idx /= 2)
            t[idx] = min(t[idx * 2], t[idx * 2 + 1]);
    }

    int q() {
        return t[1];
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector<int> arr(n);
        set<int> unique;
        vector<vector<int> > idxs(n + 1);
        for (int i = 0; i < n; i++)
        {
            cin >> arr[i];
            idxs[arr[i]].push_back(i);
            unique.insert(arr[i]);
        }
        
        vector<int> par(n + 1, n / 2 + n % 2);
        vector<int> nep(n + 1, n / 2);

        for (int i = 0; i < n; i += 2)
            par[arr[i]]--;
        for (int i = 1; i < n; i += 2)
            nep[arr[i]]--;

        seggy seg(n + 1, nep);
        vector<bool> in(n + 1, false);
        int out = n;
        for (int x : unique) {
            seg.mod(x, 1e9);

            for (int i : idxs[x]) {
                if (i % 2 == 1) {
                    if (i > 0)
                    {
                        if (!in[i - 1])
                            seg.mod(arr[i - 1], 1);
                        in[i - 1] = true;
                    }
                    if (i != n - 1) {
                        if (!in[i + 1] && !(i > 0 && arr[i - 1] == arr[i + 1]))
                            seg.mod(arr[i + 1], 1);
                        in[i + 1] = true;
                    }
                }
            }

            out = min(out, seg.q() + par[x]);

            for (int i : idxs[x]) {
                if (i % 2 == 1) {
                    if (i > 0)
                    {
                        if (in[i - 1] == true)
                            seg.mod(arr[i - 1], -1);
                        in[i - 1] = false;
                    }
                    if (i != n - 1)
                    {
                        if (in[i + 1] == true && (i > 0 && arr[i - 1] == arr[i + 1]))
                            seg.mod(arr[i + 1], -1);
                        in[i + 1] = false;
                    }
                }
            }

            seg.mod(x, -1e9);
        }

        cout << out <<"\n";
    }
}