#include <bits/stdc++.h>
#define pii pair<int, int>
#define ll long long
#define ld long double

using namespace std;

vector<vector<int> > graph;
vector<vector<int> > transp;

stack<int> stck;
vector<bool> visited;
void dfs1(int curr) {
    visited[curr] = true;

    for (int x : graph[curr])
        if (!visited[x])
            dfs1(x);
    stck.push(curr);
}

vector<int> sccs;
void dfs2(int curr, int scc) {
    visited[curr] = false;
    sccs[curr] = scc;
    for (int x : transp[curr])
        if (visited[x])
            dfs2(x, scc);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int T;
    cin >> T;
    while (T--) {
        graph.clear();
        transp.clear();
        visited.clear();
        sccs.clear();

        int n, m;
        cin >> n >> m;

        graph.resize(n + 1, vector<int>());
        transp.resize(n + 1, vector<int>());
        sccs.resize(n + 1, 0);

        for (int i = 0; i < m; i++) {
            int f, t;
            cin >> f >> t;
            graph[f].push_back(t);
            transp[t].push_back(f);
        }

        visited.resize(n + 1, false);
        for (int i = 1; i <= n; i++)
            if (!visited[i])
                dfs1(i);
        
        vector<int> roots;
        while (!stck.empty()) {
            int curr = stck.top();
            stck.pop();
            if (!visited[curr])
                continue;
            dfs2(curr, curr);
            roots.push_back(curr);
        }

        vector<int> deg(n + 1, 0);
        for (int i = 1; i <= n; i++) {
            for (int x : graph[i]) {
                if (sccs[i] == sccs[x])
                    continue;
                deg[sccs[x]]++;
            }
        }

        int out = roots.size();
        for (int x : roots) {
            if (deg[x] != 0)
                out--;
        }

        cout << out << "\n";
    }
}
