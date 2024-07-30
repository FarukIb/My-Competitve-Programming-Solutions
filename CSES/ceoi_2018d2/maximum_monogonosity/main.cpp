#include <bits/stdc++.h>
#define mp make_pair
#define all(a) a.begin(), a.end()

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

int get_val(vector<int> benches, int n, int m, int d) {
    if (benches[0] != 1)
    {
        benches.insert(benches.begin(), 1);
        m++;
    }
    vector<int> pref_cnt(m + 1);
    pref_cnt[0] = 1;
    for (int i = 1; i < m; i++) {
        pref_cnt[i] = (benches[i] - benches[i - 1] - 1) / d + 1 + pref_cnt[i - 1];
    }
    pref_cnt[m] = (n - benches[m - 1] - 1) / d + pref_cnt[m - 1];
    return pref_cnt[m];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int t;
    cin >> t;
    while (t--) {
        int n, m, d;
        cin >> n >> m >> d;
        vector<int> benches(m);
        for (int i = 0; i < m; i++)
            cin >> benches[i];
        if (benches[0] != 1)
        {
            benches.insert(benches.begin(), 1);
            m++;
        }

        vector<int> pref_cnt(m + 1), suf_cnt(m);
        pref_cnt[0] = 1;
        for (int i = 1; i < m; i++) {
            pref_cnt[i] = (benches[i] - benches[i - 1] - 1) / d + 1 + pref_cnt[i - 1];
        }
        pref_cnt[m] = (n - benches[m - 1]) / d + pref_cnt[m - 1];

        int out = pref_cnt[m];
        for (int to_rem = 0; to_rem < m; to_rem++) {
            if (to_rem != m - 1 and to_rem != 0) {
                int val = pref_cnt[to_rem - 1];
                val += (benches[to_rem + 1] - benches[to_rem - 1] - 1) / d;
                val += pref_cnt[m] - pref_cnt[to_rem + 1];
            } else if (to_rem == 0) {
                int f = benches[0];
                benches.erase(benches.begin());
                out = min(out, get_val(benches, n, benches.size(), d));
                benches.insert(benches.begin(), f);
            } else if (to_rem == m - 1) {
                int l = benches[m - 1];
                benches.pop_back();
                out = min(out, get_val(benches, n, benches.size(), d));
                benches.push_back(l);
            }
        }

        cout << out << "\n";
    }
}