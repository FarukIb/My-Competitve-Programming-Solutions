#include <bits/stdc++.h>
#define mp make_pair
#define all(a) a.begin(), a.end()

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

const int siz = 7;

pii movesa[256];
vector<char> moves = {'U', 'D', 'R', 'L'};

bool visited[siz][siz];

string s;
int recur(int x, int y, int j) {
    if (x == 0 and y == siz - 1) {
        if (j == siz * siz-1)
            return 1;
        else
            return 0;
    }
    if ((y == 0 || visited[x][y - 1]) and (y == siz - 1 || visited[x][y + 1])
     and (x != 0 and !visited[x - 1][y]) and (x != siz - 1 and !visited[x + 1][y]))
        return 0;
    if ((x == 0 || visited[x - 1][y]) and (x == siz - 1 || visited[x + 1][y]) and
     (y != 0 and !visited[x][y - 1]) and (y != siz - 1 and !visited[x][y + 1]))
        return 0;
    visited[x][y] = true;
    int mycnt = 0;
    for (int i = 0; i < 4; i++) {
        if (s[j] == 4 || s[j] == i) {
            int newx = x + movesa[i].first, newy = y+movesa[i].second;
            if (newx < 0 || newx >= siz || newy < 0 || newy >= siz)
                continue;
            if (visited[newx][newy])
                continue;
            mycnt += recur(newx, newy, j + 1);
        }
    }
    visited[x][y] = false;
    return mycnt;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cin >> s;
    movesa[0] = mp(0, -1);
    movesa[1] = mp(0, 1);
    movesa[2] = mp(1, 0);
    movesa[3] = mp(-1, 0);
    for (int i = 0; i < s.size(); i++) {
        if (s[i] == 'U')
            s[i] = 0;
        else if (s[i] == 'D')
            s[i] = 1;
        else if (s[i] == 'R')
            s[i] = 2;
        else if (s[i] == 'L')
            s[i] = 3;
        else
            s[i] = 4;
    }
    
    cout << recur(0, 0, 0) <<"\n";
}   