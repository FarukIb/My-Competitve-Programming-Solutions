#include <bits/stdc++.h>
#define mp make_pair

using namespace std;

typedef long long ll;
typedef pair<ll, ll> pii;

const int maxn = 1e5 + 10;

struct seggy {
    vector<ll> t;
    int n;

    seggy() {}
    seggy(int N) {
        n = N;
        t.resize(n * 2, 0);
    }

    ll query() {return t[1];}
    ll get(int idx) {return t[idx + n]; }

    void mod(int idx, ll val) {
        for (idx += n, t[idx] = val, idx /= 2; idx > 0; idx /= 2)
            t[idx] = max(t[idx * 2], t[idx * 2 + 1]);
    }
};

seggy dp1;
seggy dp2;
vector<int> par;
vector<vector<pii > > graph;

ll ans = 0;
void dfs(int curr) {
    vector<ll> dps;
    dps.push_back(0);
    for (pii e : graph[curr]) {
        if (e.first == par[curr])
            continue;
        par[e.first] = curr;
        dfs(e.first);
        dps.push_back(e.second + dp1.get(e.first));
    }
    sort(dps.begin(), dps.end());
    reverse(dps.begin(), dps.end());
    dp1.mod(curr, dps[0]); // [curr] = dps[0];
    if (dps.size() > 2)
        dp2.mod(curr, dps[0] + dps[1]); //[curr] = dps[0] + dps[1];
    else
        dp2.mod(curr, -1);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int n, q; ll w;
    cin >> n >> q >> w;
    dp1 = seggy(n + 1);
    dp2 = seggy(n + 1);
    par.resize(n + 1, 0);
    graph.resize(n + 1);

    vector<pii> edges;
    for (int i = 1; i < n; i++) {
        int f, t, w;
        cin >> f >> t >> w;
        edges.push_back({f, t});
        graph[f].push_back({t, w});
        graph[t].push_back({f, w});
    }
    dfs(1);
    ll last = 0;
    while (q--) {
        ll e, d;
        cin >> d >> e;
        d += last;
        e += last;
        d %= (n - 1);
        e %= w;

        pii myedge = edges[d]; // first guy is parent
        if (par[myedge.second] != myedge.first)
            swap(myedge.first, myedge.second);
        
        // changing the guy
        for (int i = 0; i < graph[myedge.first].size(); i++)
        {
            if (graph[myedge.first][i].first == myedge.second)
                graph[myedge.first][i].second = e;
        }

        // recalculating
        int curr = myedge.first;
        while (curr != 0) {
            vector<ll> dps;
            dps.push_back(0);
            for (pii E : graph[curr]) {
                if (E.first == par[curr]) 
                    continue;
                dps.push_back(E.second + dp1.get(E.first));
            }
            sort(dps.begin(), dps.end());
            reverse(dps.begin(), dps.end());
            dp1.mod(curr, dps[0]); // [curr] = dps[0];
            if (dps.size() > 2)
                dp2.mod(curr, dps[0] + dps[1]); //[curr] = dps[0] + dps[1];
            else
                dp2.mod(curr, -1);
            
            curr = par[curr];
        }

        ans = max(dp1.query(), dp2.query());
        cout << ans << "\n";
        last = ans;
    }
}