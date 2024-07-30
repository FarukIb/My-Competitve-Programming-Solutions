#include <bits/stdc++.h>
#define mp make_pair
#define all(a) a.begin(), a.end()

using namespace std;

typedef long long ll;
typedef pair<ll, ll> pii;
typedef vector<vector<ll> > vvi;

int k;
vvi combine(vvi beg, vvi endd) {
    vvi ans(k, vector<ll>(k, 1e18));
    for (int i = 0; i < k; i++)
        for (int j = 0; j < k; j++)
            for (int l = 0; l < k; l++)
                ans[i][l] = min(ans[i][l], beg[i][j] + endd[j][l]);
    return ans;
}

const int lg = 18;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int n, m, q;
    cin >> k >> n >> m >> q;
    vector<vector<vvi> > lift(lg, vector<vvi> (n / k + 1, vvi(k, vector<ll>(k, 1e18))));
    for (int i = 0; i < m; i++) {
        int f, t, p;
        cin >>f >> t >> p;
        lift[0][f / k][f % k][t % k] = p;
    }

    
    int num_lay = n / k + 1;
    for (int bit = 1; bit < lg; bit++)
        for (int i = num_lay - (1 << (bit - 1)) - 1; i >= 0; i--) 
            lift[bit][i] = combine(lift[bit - 1][i], lift[bit - 1][i + (1 << (bit - 1))]);


    while (q--) {
        int f, t;
        cin >> f >> t;
        int SF = f / k, ST = t / k;
        vvi ans(k, vector<ll>(k, 1e18));
        ans[f % k][f % k] = 0;
        int diff = ST - SF;
        for (int i = 0; i < lg; i++) {
            if (((1 << i) & diff) != 0) {
                ans = combine(ans, lift[i][SF]);
                SF += (1 << i);
            }
        }

        if (ans[f % k][t % k] == 1e18)
            cout << "-1\n";
        else
            cout << ans[f % k][t % k] << "\n";
    }
}