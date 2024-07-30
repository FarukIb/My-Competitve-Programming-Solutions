#include <bits/stdc++.h>
#define mp make_pair
#define all(a) a.begin(), a.end()

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

vector<int> dp, g;

void dfs(int cur, int par, vector<vector<int>>& graph){
    for (int a : graph[cur])
    {
        if (a == par)
            continue;
        dfs(a, cur, graph);
        dp[cur] = max(dp[a] + 1, dp[cur]);
    }
}

void dfs2(int curr, int par, vector<vector<int> > &graph) {
    int naj = -1, dr = -1;
    for (int a : graph[curr]) {
        if (a == par)
            continue;
        int c(dp[a]);
        if (c > naj)
            dr = naj, naj = c;
        else
            dr = max(dr, c);
    }

    for (int a : graph[curr])
    {
        if (a == par)
            continue;
        
        g[a] = max(g[a], g[curr] + 1);
        if (dp[a] == naj)
            g[a] = max(g[a], dr + 2);
        else
            g[a] = max(g[a], naj + 2);
        dfs2(a, curr, graph);
    }
} 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int n;
    cin >> n;
    dp = g = vector<int> (n + 1);
    vector<vector<int>> graph(n + 1);
    for (int i = 1; i < n; i++)
    {
        int a, b;
        cin >> a >>b;
        graph[a].push_back(b);
        graph[b].push_back(a);

    }
    dfs(1, 0, graph);
    dfs2(1, 0, graph);
    
    for (int i = 1; i <= n; i++)
        cout << max(dp[i], g[i]) << " ";
    cout << endl;
}