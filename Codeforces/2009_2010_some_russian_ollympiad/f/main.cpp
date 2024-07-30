#include <bits/stdc++.h>
#define pii pair<int, int>
#define ll long long
#define ld long double

using namespace std;

vector<vector<int> > grid;
queue<pii> que;
set<pii> inqueue;
bool ok = true;

vector<pii> ops = {pii(0, 1), pii (0, -1), pii(-1, 0), pii(1, 0)};

void dewit(pii coords) {
    int X = coords.first, Y = coords.second;

    if (grid[X][Y] != 1)
    {
        ok = false;
        return;
    }
    grid[X][Y]--;

    for (pii op : ops) {
        int x = X + op.first, y = Y + op.second;
        if (grid[x][y] == 0)
            continue;

        if (inqueue.count(pii(x, y)))
        {
            ok = false;
            return;
        }
        grid[x][y]--;

        if (grid[x][y] == 1) {
            que.push(pii(x, y));
            inqueue.insert(pii(x, y));
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    ifstream fin("input.txt");
    ofstream fout("output.txt");

    int n, m;
    fin >> n >> m;
    grid.resize(n + 2, vector<int>(m + 2, 0));
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            fin >> grid[i][j];
            if (grid[i][j] == 1)
            {
                que.push(pii(i, j));
                inqueue.insert(pii(i, j));
            }
        }
    }

    vector<pii> out;
    while (que.size() > 0) {
        pii cur = que.front();
        que.pop();
        dewit(cur);
        if (!ok) {
            fout << "No solution\n";
            return 0;
        }
        out.push_back(cur);

        if (out.size() > n * m) {
            fout << "No solution\n";
            return 0;
        }
    }

    int sum = 0;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            sum += grid[i][j];
    if (sum)
        fout << "No solution\n";
    else
    {
        for (int i = n * m - 1; i >= 0; i--)
            fout << out[i].first << " " << out[i].second << "\n";
    }
    
    return 0;
}
