#include <bits/stdc++.h>
#define mp make_pair
#define all(a) a.begin(), a.end()

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

const ll mod = 1e9 + 7;

vector<vector<int> > graph;
vector<vector<int> > transp;

stack<int> stck;
vector<bool> visited;
void dfs1(int curr, vector<vector<int> > &graph) {
    visited[curr] = true;
    for (int a : graph[curr])
        if (!visited[a])
            dfs1(a, graph);
    stck.push(curr);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int n;
    cin >> n;
    vector<ll> cost(n+1);
    for (int i = 0; i < n; i++)
        cin >> cost[i + 1];
    graph.resize(n+1);
    transp = graph;

    int m;
    cin >> m;
    for (int i = 0; i < m; i++) {
        int f, t;
        cin >>f >>t;
        graph[f].push_back(t);
        transp[t].push_back(f);
    }
    
    visited.resize(n+1);
    for (int i = 1; i <= n; i++) {
        if (!visited[i])
            dfs1(i, graph);
    }
    fill(all(visited), false);
    ll comp = 0, numways = 1;
    auto mystck = stck;
    stck = stack<int>();
    while (!mystck.empty()) {
        int curr = mystck.top(); mystck.pop();
        if (!visited[curr]) {
            dfs1(curr, transp);
            vector<ll> cmparr;
            while (!stck.empty())
            {
                cmparr.push_back(cost[stck.top()]);
                stck.pop();
            }
            ll min_el = *min_element(all(cmparr));
            ll cnt = count(all(cmparr), min_el);
            comp += min_el;
            numways *= cnt;
            numways %= mod;
        }
    }

    cout << comp << " " << numways << "\n";
}
