#include <bits/stdc++.h>
#define pii pair<int, int>
#define ll long long
#define ld long double

using namespace std;

ll n, a, b, c, d;
vector<int> perm;

vector<ll> len;
vector<ll> linkk;
void dfs(int start, int curr, int clen) {
    if (clen != 0 && curr == start)
    {
        len[start] = clen;
        return;
    }
    linkk[curr] = start;

    dfs(start, perm[curr], clen + 1);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    cin >> n >> a >> b >> c >> d;
    a--, b--;
    c++;

    perm.resize(n + 1, 0);
    for (int i = 1; i <= n; i++)
        cin >> perm[i];

    // cycle len
    len.resize(n + 1, 0);
    linkk.resize(n + 1, 0);

    for (int i = 1; i <= n; i++)
    {
        if (linkk[i] == 0)
            dfs(i, i, 0);
    }

    ll cyc = 1;
    for (int i = c; i <= n - d; i++) {
        cyc = cyc / __gcd(cyc, len[linkk[i]]) * len[linkk[i]];
        if (cyc > b) {
            cout << "0\n";
            return 0;
        }
    }
    
    ll ans = b / cyc;
    if (a == 0)
        ans++;
    else
        ans -= (a - 1) / cyc;
    cout << ans << "\n";
}
