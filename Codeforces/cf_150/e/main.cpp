#include <bits/stdc++.h>
#define mp make_pair
#define x first
#define y second

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

void update_point(pii &curr, char dir, int magnitue) {
    if (dir == 'U')
        curr.y += magnitue;
    if (dir == 'D')
        curr.y -= magnitue;
    if (dir == 'R')
        curr.x += magnitue;
    if (dir == 'L')
        curr.x -= magnitue;
}

void colour(pii f, pii t, vector<vector<char> > &grid) {
    if (f.x == t.x) {
        if (f.y < t.y) {
            for (int i = f.y; i <= t.y; i++)
                grid[f.x][i] = 'x';
        }
        else {
            for (int i = t.y; i <= f.y; i++)
                grid[f.x][i] = 'x';
        }
    }
    else {
        if (f.x < t.x) {
            for (int i = f.x; i <= t.x; i++)
                grid[i][f.y] = 'x';
        }
        else {
            for (int i = t.x; i <= f.x; i++)
                grid[i][f.y] = 'x';
        }
    }
}

ll getArea(pii a, pii b) {
    ll side1 = abs(a.y - b.y);
    ll side2 = abs(a.x - b.x);
    return side1 * side2;
}

void dfs(pii curr, vector<vector<char> > &grid) {
    if (curr.x < 0 || curr.y < 0 || curr.x >= grid.size() || curr.y >= grid[0].size())
        return;
    if (grid[curr.x][curr.y] == 'v' || grid[curr.x][curr.y] == 'x')
        return;
    grid[curr.x][curr.y] = 'v';
    dfs(mp(curr.x + 1, curr.y), grid);
    dfs(mp(curr.x - 1, curr.y), grid);
    dfs(mp(curr.x, curr.y + 1), grid);
    dfs(mp(curr.x, curr.y - 1), grid);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int n;
    cin >> n;
    pii mini_uncompressed(0, 0);
    pii maxi_uncompressed(0, 0);
    vector<pii> points_uncompressed;
    pii curr(0, 0);
    points_uncompressed.push_back(curr);
    for (int i = 0; i < n; i++) {
        char dir; int magnitue;
        cin >> dir;
        cin >> magnitue;

        update_point(curr, dir, magnitue);

        mini_uncompressed.x = min(mini_uncompressed.x, curr.x);
        mini_uncompressed.y = min(mini_uncompressed.y, curr.y);
        maxi_uncompressed.x = max(maxi_uncompressed.x, curr.x);
        maxi_uncompressed.y = max(maxi_uncompressed.y, curr.y);
        points_uncompressed.push_back(curr);
    }

    set<int> xs;
    set<int> ys;
    for (pii point : points_uncompressed) {
        xs.insert(point.x);
        xs.insert(point.x - 1);
        xs.insert(point.x + 1);

        ys.insert(point.y);
        ys.insert(point.y - 1);
        ys.insert(point.y + 1);
    }
    map<int, int> x_map;
    map<int, int> rev_x_map;
    map<int, int> y_map;
    map<int, int> rev_y_map;
    int k = 0;
    for (int s : xs) {
        x_map[s] = k;
        rev_x_map[k] = s;
        k++;
    }
    k = 0;
    for (int s : ys) {
        y_map[s] = k;
        rev_y_map[k] = s;
        k++;
    }


    vector<pii> points;
    for (pii point : points_uncompressed) {
        points.push_back(mp(x_map[point.x], y_map[point.y]));
    }
    pii maxi(x_map[maxi_uncompressed.x], y_map[maxi_uncompressed.y]);

    vector<vector<char> > grid(xs.size() + 1, vector<char>(ys.size() + 1, ' '));
    for (int i = 1; i < points.size(); i++) {
        colour(points[i - 1], points[i], grid);
    }

    dfs(mp(0, 0), grid);

    ll out = 0;
    for (int i = 0; i < grid.size() - 1; i++) {
        for (int j = 0; j < grid[0].size() - 1; j++) {
            if (grid[i][j] == 'v')
                continue;
            pii pnt1(rev_x_map[i], rev_y_map[j]), pnt2(rev_x_map[i + 1], rev_y_map[j + 1]);
            ll area = getArea(pnt1, pnt2);
            out += area;
        }
    }
    cout << out << "\n";
}