#include <bits/stdc++.h>

using namespace std;

vector<vector<int> > graph;
vector<vector<int> > dp;

int dfs(int curr, int used, int p) {
    if (dp[curr][used] != -1)
        return dp[curr][used];

    int ans = used;
    for (int x : graph[curr]) {
        if (x == p)
            continue;
        if (used)
            ans += min(dfs(x, 1, curr), dfs(x, 0, curr));
        else
            ans += dfs(x, 1, curr);
    }

    dp[curr][used] = ans;
    return ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int n;
    cin >> n;
    graph.resize(n + 1);
    dp.resize(n + 1, vector<int>(2, -1));
    for (int i = 0; i < n - 1; i++) {
        int x, y;
        cin >> x >> y;
        graph[x].push_back(y);
        graph[y].push_back(x);
    }

    cout << min(dfs(1, 0, 0), dfs(1, 1, 0)) << "\n";
}