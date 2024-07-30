#include <bits/stdc++.h>
#define pii pair<int, int>
#define ll long long
#define ld long double

using namespace std;

vector<string> grid;
int n, s;

void expand(queue<pii>& bees, vector<string>& mat, vector<vector<bool> > &expanded ) {

    queue<pii> newque;
    while (!bees.empty()) {
        pii curr = bees.front();
        bees.pop();

        if (expanded[curr.first][curr.second])
            continue;
        
        if (mat[curr.first + 1][curr.second] == 'G' || mat[curr.first + 1][curr.second] == 'M')
            mat[curr.first + 1][curr.second] = 'H', newque.push({curr.first + 1, curr.second});
        if (mat[curr.first - 1][curr.second] == 'G' || mat[curr.first - 1][curr.second] == 'M')
            mat[curr.first - 1][curr.second] = 'H', newque.push({curr.first - 1, curr.second});
        if (mat[curr.first][curr.second + 1] == 'G' || mat[curr.first][curr.second + 1] == 'M')
            mat[curr.first][curr.second + 1] = 'H', newque.push({curr.first, curr.second + 1});
        if (mat[curr.first][curr.second - 1] == 'G' || mat[curr.first][curr.second - 1] == 'M')
            mat[curr.first][curr.second - 1] = 'H', newque.push({curr.first, curr.second - 1});
        expanded[curr.first][curr.second] = true;
    }

    bees = newque;
}

bool possible(int wait, queue<pii> bees, pii start, pii endd) {
    vector<vector<bool> > expanded(n + 2, vector<bool>(n + 2, false));
    vector<string> mat = grid;
    mat[start.first][start.second] = 'G';


    for (int i = 0; i < wait; i++)
        expand(bees, mat, expanded);

    vector<vector<bool> > visited(n + 2, vector<bool>(n + 2, false));
    int tim = s;
    queue<pair<int, pii> > que;

    que.push({0, {start.first, start.second}});
    while (!que.empty())
    {
        pair<int, pii> curr = que.front();
        que.pop();

        if (curr.first == tim) {
            expand(bees, mat, expanded);
            tim += s;
        }

        if (!(mat[curr.second.first][curr.second.second] == 'G' || mat[curr.second.first][curr.second.second] == 'D')
         || visited[curr.second.first][curr.second.second])
            continue;
        visited[curr.second.first][curr.second.second] = true;

        que.push({curr.first + 1, {curr.second.first + 1, curr.second.second}});
        que.push({curr.first + 1, {curr.second.first - 1, curr.second.second}});
        que.push({curr.first + 1, {curr.second.first, curr.second.second + 1}});
        que.push({curr.first + 1, {curr.second.first, curr.second.second - 1}});
    }
    
    return visited[endd.first][endd.second];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    cin >> n >> s;
    grid.resize(n + 2);
    string wall;
    for (int i = 0; i < n + 2; i++)
        wall += 'T';
    grid[0] = wall, grid[n + 1] = wall;
    for (int i = 1; i <= n; i++) {
        string curr = "T";
        string inp;
        cin >> inp;
        curr += inp;
        curr += 'T';
        grid[i] = curr;
    }

    queue<pii> bees;
    pii start, endd;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (grid[i][j] == 'D')
                endd = {i, j};
            else if (grid[i][j] == 'H')
                bees.push({i, j});
            else if (grid[i][j] == 'M')
                start = {i, j};
        }
    }
    
    int l = 0, r = 10 * n;
    while (l < r) {
        int mid = (l + r) / 2;
        if (possible(mid, bees, start, endd))
            l = 1 + mid;
        else
            r = mid;
    }

    cout << l - 1 << "\n";
}
