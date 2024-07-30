#include <bits/stdc++.h>
#define pii pair<int, int>
#define ll long long
#define ld long double

using namespace std;

vector<vector<int> > graph;
vector<vector<int> > transp;
vector<bool> visited;

stack<int> cool;

void dfs1(int curr) {
    visited[curr] = true;
    for (int x : graph[curr])
        if (!visited[x])
            dfs1(x);
    cool.push(curr);
}

void dfs2(int curr, vector<int> &currGuy) {
    visited[curr] = true;
    currGuy.push_back(curr);
    for (int x : transp[curr])
        if (!visited[x])
            dfs2(x, currGuy);
}

int cmp(vector<int> a, vector<int> b) { return a[0] < b[0]; }

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    //fstream fout("out.txt");
    bool ok = false;
    while (1) {
        int n;
        cin >> n;
        if (n == 0)
            break;
        
        if (ok)
            cout << "\n";
        ok = true;

        graph.clear();
        graph.resize(30, vector<int>());

        transp.clear();
        transp.resize(30, vector<int>());

        visited.clear();
        visited.resize(30, false);

        set<int> used;
        for (int i = 0; i < n; i++) {
            set<int> left; char target;
            for (int j = 0; j < 5; j++) {
                char x;
                cin >> x; x -= 'A'; left.insert(x);
                used.insert(x);
            }
            cin >> target;
            target -= 'A';
            left.erase(target);

            for (int x : left) {
                graph[target].push_back(x);
                transp[x].push_back(target);
            }
                
        }

        for (int x : used) {
            if (visited[x])
                continue;
            dfs1(x);
        }

        fill(visited.begin(), visited.end(), false);
        vector<vector<int> > out;
        while (!cool.empty()) {
            int x = cool.top(); cool.pop();
            if (visited[x])
                continue;

            vector<int> currGuy;
            dfs2(x, currGuy);
            sort(currGuy.begin(), currGuy.end());
            out.push_back(currGuy);
        }
        
        sort(out.begin(), out.end(), cmp);
        for (vector<int> curr : out) {
            cout << (char)('A' + curr[0]);
            for (int i = 1; i < curr.size(); i++)
                cout << " " << (char)('A' + curr[i]);
            cout << "\n";
        }
    }
}
