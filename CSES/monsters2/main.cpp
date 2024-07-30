#include <bits/stdc++.h>
#define mp make_pair
#define all(a) a.begin(), a.end()

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int n, m;
    cin >> n >> m;
    vector<string> mat(n);
    for (int i = 0; i < n; i++)
        cin >> mat[i];
    pii my;
    queue<pii> monsters;
    vector<vector<int> > mindist(n, vector<int>(m, 1e9));
    vector<pii> exits;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (mat[i][j] == 'M')
                monsters.push(mp(i, j)), mindist[i][j] = 0;
            else if (mat[i][j] == 'A')
                my = mp(i, j);
            
            if (i == 0 || i == n - 1 ||j == 0 || j == m - 1 and mat[i][j] != '#')
                exits.push_back(mp(i, j));
        }
    }

    vector<pii> moves = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
    
    while (!monsters.empty()) {
        pii my = monsters.front(); monsters.pop();
        for (pii move : moves) {
            pii coord = {my.first + move.first, my.second + move.second};
            if (coord.first < 0 || coord.first >= n || coord.second < 0 || coord.second >= m)
                continue;
            if (mindist[coord.first][coord.second] != 1e9 || mat[coord.first][coord.second] == '#')
                continue;
            mindist[coord.first][coord.second] = mindist[my.first][my.second] + 1;
            monsters.push(coord);
        }
    }

    queue<pii> que; vector<vector<pii> > par(n, vector<pii>(m, mp(1e9, 1e9)));
    vector<vector<int> > dist(n, vector<int>(m, 1e9));
    par[my.first][my.second] = mp(-1, -1);
    dist[my.first][my.second] = 0;
    que.push(my);
    while (!que.empty()) {
        pii my = que.front(); que.pop(); int my_dist = dist[my.first][my.second];
        for (pii move : moves) {
            pii coord = {my.first + move.first, my.second + move.second};
            if (coord.first < 0 || coord.first >= n || coord.second < 0 || coord.second >= m)
                continue;
            if (mat[coord.first][coord.second] == '#')
                continue;
            int n_dist = my_dist + 1;
            if (n_dist >= mindist[coord.first][coord.second])
                continue;
            par[coord.first][coord.second] = my;
            dist[coord.first][coord.second] = n_dist;
            que.push(coord);
        }
    }

    for (pii ex : exits) {
        if (dist[ex.first][ex.second] == 1e9)
            continue;
        
        vector<pii> path;
        pii curr = ex;
        while (curr != mp(-1, -1)) {
            path.push_back(curr);
            curr = par[curr.first][curr.second];
        }

        string m = "";
        for (int i = path.size() - 1; i > 0; i--) {
            pii a(path[i - 1].first - path[i].first, path[i - 1].second - path[i].second);

            if (a.first == -1)
                m += 'U';
            else if (a.first == 1)
                m += 'D';
            else if (a.second == 1)
                m += 'R';
            else 
                m += 'L';
        }

        cout << "YES\n";
        cout << m.size() << "\n";
        cout << m << "\n";
        return 0;
    }

    cout << "NO\n";
}