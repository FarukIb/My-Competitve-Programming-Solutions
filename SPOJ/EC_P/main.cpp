#include <bits/stdc++.h>
#define mp make_pair
#define all(a) a.begin(), a.end()

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

vector<vector<int> > graph;
vector<int> dp, par, hght;
vector<bool> visited;

vector<pii> bridges;

void dfs(int curr) {
    int n_up = 0, n_down = 0;
    visited[curr] = true;
    for (int a : graph[curr]) {
        if (a == par[curr])
            continue;
        if (visited[a]) {
            if (hght[curr] > hght[a])
                dp[curr]++, dp[a]--;
            continue;
        }
        par[a] = curr;
        hght[a] = hght[curr] + 1;
        dfs(a);
        dp[curr] += dp[a];
    }

    if (dp[curr] == 0 and curr != 1)
        bridges.push_back(pii(min(curr, par[curr]), max(curr, par[curr])));
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int t, tcnum = 0;
    cin >> t;
    while (t--) {
        tcnum++;

        int n, m;
        cin >> n >> m;
        graph = vector<vector<int> > (n + 1);
        dp = par = hght = vector<int> (n + 1);
        visited = vector<bool> (n + 1);

        for (int i = 0; i < m; i++) {
            int f, t;
            cin >> f >> t;
            graph[f].push_back(t);
            graph[t].push_back(f);
        }

        dfs(1);
        sort(all(bridges));
        cout << "Caso #" << tcnum << "\n";
        if (bridges.empty()) {
            cout << "Sin bloqueos" << "\n";
        } else {
            cout << bridges.size() << "\n";
            for (pii a : bridges)
                cout << a.first << " " << a.second << "\n";
        }
        bridges.clear();
    }   
}