#include <bits/stdc++.h>
#define mp make_pair

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

vector<vector<int> > graph;
vector<int> par;
vector<int> phase;

vector<int> cyc;
void dfs(int curr) {
    if (!cyc.empty())
        return;
    if (phase[curr] == 1) {
        cyc.push_back(curr);
        int guy = curr;
        do {
            guy = par[guy];
            cyc.push_back(guy);
        } while (guy != curr);
        return;
    }
    else if (phase[curr] == 2)
        return;
    
    phase[curr] = 1;
    for (int s : graph[curr]) {
        if (s == par[curr])
            continue;
        par[s] = curr;
        dfs(s);
    }
    phase[curr] = 2;
} 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int n, m;
    cin >> n >> m;
    phase.resize(n + 1, 0);
    par.resize(n + 1, 0);
    graph.resize(n + 1);
    
    for (int i = 0; i < m; i++) {
        int f, t;
        cin >>f >> t;
        graph[f].push_back(t);
        graph[t].push_back(f);
    }

    for (int i = 1; i <= n; i++)
        if (phase[i] == 0) 
            dfs(i);
    
    if (cyc.empty())
        cout << "IMPOSSIBLE\n";
    else {
        cout << cyc.size() << "\n";
        for (int s : cyc)
            cout << s << " ";
        cout << "\n";
    }
}