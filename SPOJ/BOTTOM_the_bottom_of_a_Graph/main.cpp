#include <bits/stdc++.h>
#define pii pair<int, int>
#define ll long long
#define ld long double

using namespace std;

vector<int> SCC;
vector<bool> visited;

vector<vector<int> > graph;
vector<vector<int> > transp;
int n;

stack<int> cool;
void dfs1(int curr) {
    visited[curr] = true;

    for (int x : graph[curr]) {
        if (visited[x])
            continue;
        dfs1(x);
    }

    cool.push(curr);
}

void dfs2(int curr, int id) {
    SCC[curr] = id;

    for (int x : transp[curr]) {
        if (SCC[x] != 0)
            continue;
        dfs2(x, id);
    }
}

bool vibeCheck(int curr, int id) {
    if (SCC[curr] != id)
        return false;
    visited[curr] = true;
    for (int x : graph[curr]) {
        if (SCC[x] != id)
            return false;
        if (visited[x] == true)
            continue;
        if (vibeCheck(x, id) == false)
            return false;
    }
    return true;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    while (cin >> n) {
        if (n == 0)
            break;
        graph.clear();
        transp.clear();
        cool = stack<int>();
        SCC.clear();
        visited.clear();
        
        SCC.resize(n + 1, 0);
        visited.resize(n + 1, false);

        graph.resize(n + 1, vector<int>());
        transp.resize(n + 1, vector<int>());

        int m;
        cin >> m;
        for (int i = 0; i < m; i++) {
            int f, t;
            cin >> f >> t;
            graph[f].push_back(t);
            transp[t].push_back(f);
        }

        for (int i = 1; i <= n; i++) {
            if (visited[i])
                continue;
            dfs1(i);
        }
        fill(visited.begin(), visited.end(), false);

        int id = 1;
        while (!cool.empty()) {
            int x = cool.top();
            cool.pop();
            if (SCC[x] > 0)
                continue;

            dfs2(x, id++);
        }

        fill(visited.begin(), visited.end(), false);
        set<int> vibe;
        for (int i = 1; i <= n; i++) {
            if (visited[i])
                continue;
            if (vibeCheck(i, SCC[i]))
                vibe.insert(SCC[i]);
        }

        vector<int> out;
        
        for (int i = 1; i <= n; i++) {
            if (vibe.find(SCC[i]) != vibe.end())
                out.push_back(i);
        }

        if (out.empty())
            cout << endl;
        else {
            cout << out[0];
            for (int i = 1; i < out.size(); i++)
                cout << " " << out[i];
            cout << endl;
        }
    }
}
