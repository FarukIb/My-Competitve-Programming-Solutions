#include <bits/stdc++.h>
#define pii pair<int, int>
#define ppiii pair<pii, int>
#define ll long long
#define ld long double

using namespace std;

int n, w, h;

vector<string> grid;

// FINDING SHORTEST PATH TO EACH
string wall = "#######################################################################";

vector<int> bfs(pii start) {
    vector<int> out(n);

    queue<ppiii> que;
    que.push(ppiii(start, 0));
    vector<vector<bool> > visited(w, vector<bool>(h, false));
    while (!que.empty()) {
        ppiii curr = que.front(); que.pop();

        int x = curr.first.first, y = curr.first.second;
        if (visited[x][y] || grid[x][y] == '#')
            continue;
        visited[x][y] = true;

        if (grid[x][y] != 'B' && grid[x][y] != '.')
            out[grid[x][y]] = curr.second;
        
        que.push(ppiii(pii(x + 1, y), curr.second + 1));
        que.push(ppiii(pii(x - 1, y), curr.second + 1));
        que.push(ppiii(pii(x, y + 1), curr.second + 1));
        que.push(ppiii(pii(x, y - 1), curr.second + 1));
    }
}

// MIN COST MAX FLOW
vector<vector<int> > mat;
vector<vector<int> > flow;


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int T;
    cin >> T;
    while (T--) {
        cin >> w >> h;
        w += 2, h += 2, n = 0;
        grid.resize(w);
        grid[0] = wall, grid[w - 1] = wall;
        for (int i = 1; i <= w; i++)
        {
            string curr = "#";
            cin >> grid[i];
            curr += grid[i];
            curr += '#';
            grid[i] = curr;
        }
        
        vector<pii> coords;
        char x = 0;
        for (int i = 0; i < w; i++) {
            for (int j = 0; j < h; j++) {
                if (grid[i][j] == 'X')
                    grid[i][j] = x, x++;
                else if (grid[i][j] == 'B')
                    coords.push_back(pii(i, j));
            }
        }
        n = coords.size();

        mat.clear();
        for (int i = 0; i < n; i++) 
            mat.push_back(bfs(coords[i]));

        
    }
}
