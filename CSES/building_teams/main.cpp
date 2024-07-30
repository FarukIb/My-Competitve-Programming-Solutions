#include <bits/stdc++.h>
#define mp make_pair

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

vector<vector<int> > graph;
vector<int> colour;

bool possible = true;
void dfs(int curr, int col) {
    if (!possible)
        return;
    colour[curr] = col;
    for (int s : graph[curr]) {
        if (colour[s] == col)
        {
            possible = false;
            return;
        }
        else if (colour[s] == 0)
            dfs(s, 3 - col); // ako je col = 2 onda je 3 - col = 1, ako je col 1, onda je 3 - col = 2
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int n, m;
    cin >> n >> m;

    graph.resize(n + 1);
    colour.resize(n + 1, 0);
    for (int i = 0; i < m; i++) {
        int f, t;
        cin >> f >> t;
        graph[f].push_back(t);
        graph[t].push_back(f);
    }

    for (int i = 1; i <= n; i++)
        if (colour[i] == 0)
            dfs(i, 1);
    
    if (possible == false)
        cout << "IMPOSSIBLE\n";
    else {
        for (int i = 1; i <= n; i++)
            cout << colour[i] << " ";
        cout << "\n";
    }
}