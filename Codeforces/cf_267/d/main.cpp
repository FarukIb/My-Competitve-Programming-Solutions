#include <bits/stdc++.h>
#define pii pair<ll, ll>
#define ll long long
#define ld long double

using namespace std;

// STRING PROCCESSING

map<string, ll> idx;
vector<pii> vals;
//map<string, pii> val;
pii getVal(string s) {
    //if (val.find(s) != val.end())
    //    return val[s];

    pii out(0, s.size());
    for (ll i = 0; i < s.size(); i++)
        if (s[i] == 'r') 
            out.first++;
    return out;
}

string convert(string s) {
    string out = "";
    for (ll i = 0; i < s.size(); i++)
        out += tolower(s[i]);
    return out;
}

// FIRST GRAPH
vector<vector<ll> > graph;
vector<vector<ll> > transp;

void processNew(string s) {
    s = convert(s);
    if (idx.find(s) == idx.end())
    {
        idx[s] = idx.size();
        vals.push_back(getVal(s));
        graph.push_back(vector<ll>());
        transp.push_back(vector<ll>());
    }
}

// FINDING SCCs
vector<ll> SCC;
vector<set<ll>> condGraph;
vector<pii> mini;
stack<ll> stck;

vector<bool> visited;
void dfs1(ll curr) {
    visited[curr] = true;
    for (ll x : graph[curr])
        if (!visited[x])
            dfs1(x);
    stck.push(curr);
}

void dfs2(ll curr, ll id) {
    visited[curr] = false;
    SCC[curr] = id;
    for (ll x : transp[curr])
        if (visited[x])
            dfs2(x, id);
}

// DP ON CONDENGRAPH
vector<pii> dp;
pii dpp(ll curr) {
    if (dp[curr] != pii(1e9, 1e9))
        return dp[curr];
    if (visited[curr])
        return pii(1e9, 1e9);
    visited[curr] = true;

    pii out = mini[curr];
    for (ll x : condGraph[curr])
        out = min(out, dpp(x));
    return dp[curr] = out;

}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    // PROCESSING INPUT

    ll m;
    cin >> m;
    vector<string> sentence(m);
    for (ll i = 0; i < m; i++)
    {
        cin >> sentence[i];
        sentence[i] = convert(sentence[i]);

        processNew(sentence[i]);
    }

    ll n;
    cin >> n;
    for (ll i =0 ; i < n; i++) {
        string f, t;
        cin >> f >> t;
        f = convert(f);
        t = convert(t);

        processNew(f);
        processNew(t);

        graph[idx[f]].push_back(idx[t]);
        transp[idx[t]].push_back(idx[f]);
    }


    // FINDING SCCs
    ll currSCC = 0;
    visited.resize(idx.size(), false);
    for (ll i = 0; i < idx.size(); i++) {
        if (visited[i])
            continue;
        dfs1(i);
    }

    SCC.resize(idx.size() + 1);
    while (!stck.empty()) {
        ll curr = stck.top(); stck.pop();
        if (!visited[curr])
            continue;
        dfs2(curr, currSCC++);
    }
    mini.resize(currSCC, pii(1e9, 1e9));
    condGraph.resize(currSCC, set<ll>());

    for (ll f = 0; f < idx.size(); f++)  {
        mini[SCC[f]] = min(mini[SCC[f]], vals[f]);

        for (ll t : graph[f]) {
            ll F = SCC[f], T = SCC[t];

            condGraph[F].insert(T);
        }
    }

    // doing the DP
    dp.resize(currSCC + 1, pii(1e9, 1e9));
    for (ll i = 0; i < currSCC; i++)
        dpp(i);

    fill(visited.begin(), visited.end(), false);
    pii out(0, 0);
    for (ll i = 0; i < m; i++)
        out.first += dp[SCC[idx[sentence[i]]]].first, out.second += dp[SCC[idx[sentence[i]]]].second;
    
    cout << out.first << " " << out.second << "\n";
}
