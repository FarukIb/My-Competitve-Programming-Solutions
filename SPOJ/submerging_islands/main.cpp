#include <bits/stdc++.h>
#define mp make_pair
#define all(a) a.begin(), a.end()

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

vector<vector<int> > graph;
vector<int> dp, par, hght;
vector<bool> visited, guys;

int out = 0;

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
        if (dp[a] == 0 and curr != 1)
            guys[curr] = true;
        dp[curr] += dp[a];
    }

    if (curr == 1 and graph[curr].size() > 1)
        guys[curr] = true;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    while (1) {
        int n, m;
        cin >> n >> m;
        if (n == 0 and m == 0)
            break;
        graph = vector<vector<int> > (n + 1);
        dp = par = hght = vector<int> (n + 1);
        visited = guys = vector<bool> (n + 1);
        out = 0;

        for (int i = 0; i < m; i++) {
            int f, t;
            cin >> f >> t;
            graph[f].push_back(t);
            graph[t].push_back(f);
        }

        dfs(1);
        cout << count(all(guys), true) << "\n";
    }   
}