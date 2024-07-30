#include <bits/stdc++.h>
#define mp make_pair

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

char get(pii f, pii t) {
    if (f.first > t.first)
        return 'D';
    if (f.first < t.first)
        return 'U';
    if (f.second > t.second)
        return 'R';
    if (f.second < t.second)
        return 'L';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int n, m;
    cin >> n >> m;
    vector<string> grid(n);
    for (int i = 0; i < n; i++)
        cin >> grid[i];
    
    queue<pii> mon_q;
    queue<pii> guy_q;
    vector<vector<int> > mon_dis(n, vector<int>(m, 1e9));
    vector<vector<int> > my_dis(n, vector<int>(m, 1e9));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (grid[i][j] == 'A')
            {
                guy_q.push(pii(i, j));
                my_dis[i][j] = 0;
            }
            if (grid[i][j] == 'M')
            {
                mon_q.push(pii(i, j));
                mon_dis[i][j] = 0;
            }
        }
    }

    vector<pii> moves = {mp(0, 1), mp(0, -1), mp(1, 0), mp(-1, 0)};
    while (!mon_q.empty()) {
        pii curr = mon_q.front(); mon_q.pop();
        for (pii s : moves) {    
            pii neww = mp(s.first + curr.first, s.second + curr.second);
            if (neww.first < 0 || neww.second < 0 || neww.first >= n || neww.second >= m)
                continue;
            if (grid[neww.first][neww.second] == '#' || mon_dis[neww.first][neww.second] != 1e9)
                continue;
            mon_q.push(neww);
            mon_dis[neww.first][neww.second] = mon_dis[curr.first][curr.second] + 1;
        }
    }

    vector<vector<pii> > par(n, vector<pii>(m, pii(-1, -1))); 
    while (!guy_q.empty()) {
        pii curr = guy_q.front(); guy_q.pop();
        for (pii s : moves) {
            pii neww = mp(s.first + curr.first, s.second + curr.second);
            if (neww.first < 0 || neww.second < 0 || neww.first >= n || neww.second >= m)
                continue;
            if (grid[neww.first][neww.second] == '#' || my_dis[neww.first][neww.second] != 1e9 || my_dis[curr.first][curr.second] + 1 >= mon_dis[neww.first][neww.second])
                continue;
            guy_q.push(neww);
            my_dis[neww.first][neww.second] = my_dis[curr.first][curr.second] + 1;
            par[neww.first][neww.second] = curr;
        }
    }

    pii end(-1, -1);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (!(i == 0 || i == n - 1 || j == 0 || j == m - 1))
                continue;
            if (grid[i][j] == '#')
                continue;
            if (my_dis[i][j] == 1e9)
                continue;
            end = pii(i, j);
        }
    }

    if (end == mp(-1, -1)) {
        cout << "NO\n";
        return 0;
    }

    string out = "";
    pii x = par[end.first][end.second];
    while (x != mp(-1, -1)) {
        out += get(end, x);
        end = x;
        x = par[x.first][x.second];
    }

    cout << "YES\n";
    reverse(out.begin(), out.end());
    cout << out.size() << "\n";
    cout << out << "\n";
}