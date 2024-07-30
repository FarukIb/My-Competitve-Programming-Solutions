#include <bits/stdc++.h>
#define mp make_pair
#define all(a) a.begin(), a.end()

using namespace std;

typedef long long ll;
typedef pair<ll, ll> pii;

const int COMP = 1;
const int CUST = 0;

int max_cores = 2000*50+1;

struct comp {
    ll c, f, v, type;
    comp() {}
    comp(ll a, ll b, ll C, ll typ) {
        c = a, f = b, v = C, type = typ;
    }

    bool operator<(const comp& b) const {
        if (f == b.f) 
            return type < b.type;
        return f < b.f;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    ll n, m;
    cin >> n;
    vector<comp> computers(n);
    int sum_cores = 0, dif_cores = 0;
    for (ll i = 0; i < n; i++)
    {
        cin >> computers[i].c >> computers[i].f >> computers[i].v;
        computers[i].v = -computers[i].v;
        computers[i].type = COMP;
        sum_cores += computers[i].c;
    }
    cin >> m;
    computers.resize(n+m);
    for (ll i = 0; i < m; i++)
    {  
        cin >> computers[i+n].c >> computers[i+n].f >> computers[i+n].v;
        computers[i+n].c = -computers[i+n].c;
        computers[i+n].type = CUST;
        dif_cores += computers[i+n].c;
    }

    int max_cores = sum_cores;
    sort(all(computers));
    reverse(all(computers));

    vector<ll> dp(max_cores+2, 0);
    vector<ll> prev(max_cores+2, -1e18);
    prev[0] = 0;
    for (int i = 0; i < n + m; i++) {
        for (int j = 0; j < dp.size(); j++) {
            dp[j] = prev[j];
            if (j - computers[i].c >= 0 and j - computers[i].c < (int)dp.size())
                dp[j] = max(dp[j], prev[j - computers[i].c] + computers[i].v);
        }
        swap(dp, prev);
        fill(all(dp), 0);
    }

    ll out = 0;
    for (int i = 0; i < prev.size(); i++)
        out = max(out, prev[i]);
    cout << out << "\n";
}