#include <bits/stdc++.h>
#include "game.h"

using namespace std;

vector<vector<int> > graph;
vector<vector<bool> > visited;
int N, K;

bool dfs(int u, int k) {
    if (u <= k)
        return true;
    if (!visited[k][u]) {
        visited[k][u] = true;
        for (int x : graph[u])
            if (dfs(x, k))
                return true;
    }
    return false;
}

void init(int n, int k) {
    N = n;
    K = k;

    graph.resize(n, vector<int>());
    visited.resize(k, vector<bool>(n, false));
    for (int i = 0; i < k - 1; i++)
        graph[i].push_back(i + 1), visited[i][i] = true, visited[i + 1][i + 1] = true; 
    visited[0][0] = true;
}

int add_teleporter(int u, int v) {
    graph[u].push_back(v);
    for (int i = 0; i < K; i++)
        if (visited[i][u])
            if (dfs(v, i))
                return 1;
    return 0;
}
