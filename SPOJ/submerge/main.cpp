#include <bits/stdc++.h>
#define mp make_pair
#define all(a) a.begin(), a.end()

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

vector<vector<int> > graph;
vector<int> disc;
vector<int> loww;
vector<bool> visited;

vector<bool> artic; int tim = 0;
void dfs(int curr, int par) {
    disc[curr] = loww[curr] = tim++;
    visited[curr] = true; int chh = 0;
    for (int a : graph[curr]) {
        if (a == par)
            continue;
        if (visited[a]) {
            loww[curr] = min(loww[curr], disc[a]);
        } else {
            dfs(a, curr);
            loww[curr] = min(loww[curr], loww[a]);
            if (loww[a] >= disc[curr] and par != -1)
                artic[curr] = true;
            chh++;
        }
    }
    if (curr == 1 and chh > 1)
        artic[curr] = true;
}

bool solve() {
    tim = 0;
    int n, m;
    cin >> n >> m;
    if (n == 0 and m == 0)
        return true;
    visited = vector<bool>(n + 1);
    disc = vector<int>(n+1);
    loww = vector<int>(n+1);
    graph = vector<vector<int> >(n+1);
    artic = vector<bool>(n+1);
    for (int i = 0; i < m; i++) {
        int f, t;
        cin >> f >> t;
        graph[f].push_back(t);
        graph[t].push_back(f);
    }
    dfs(1, -1);
    cout << count(all(artic), true) << "\n";
    return false;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    while (!solve()) {}
}
