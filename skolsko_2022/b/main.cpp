#include <bits/stdc++.h>
#define mp make_pair

#define x first
#define y second

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

int n, m;
vector<vector<int> > mat;
bool valid(pii my, pii guy) {
    my.x += guy.x;
    my.y += guy.y;

    if (my.x < 0 || my.x >= n)
        return false;
    if (my.y < 0 || my.y >= m)
        return false;
    if (mat[my.x][my.y] != 0)
        return false;
    return true;
}

bool valid_pickup(pii my, pii guy) {
    my.x += guy.x;
    my.y += guy.y;

    if (my.x < 0 || my.x >= n)
        return false;
    if (my.y < 0 || my.y >= m)
        return false;
    if (mat[my.x][my.y] == 0)
        return false;
    return true;
}

bool valid_lift(pii my, pii guy) {
    my.x += guy.x;
    my.y += guy.y;

    if (my.x < 0 || my.x >= n)
        return false;
    if (my.y < 0 || my.y >= m)
        return false;
    return true;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    cin >>m >>n;
    string str;
    mat.resize(n, vector<int>(m));
    pii strt;
    cin >> str;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> mat[i][j];
            if (mat[i][j] == -1)
                strt = mp(i, j), mat[i][j] = 0;
        }
    }

    map<char, pii> moves;
    moves['U'] = mp(-1, 0);
    moves['D'] = mp(1, 0);
    moves['R'] = mp(0, 1);
    moves['L'] = mp(0, -1);

    char rot = 'U';
    bool carrying = false;
    for (int q = 0; q < str.size(); q++) {
        char op = str[q];
        if (op == 'U' || op == 'D' ||op == 'R' ||op == 'L') {
            if (valid(strt, moves[op]))
            {
                strt.x += moves[op].x;
                strt.y += moves[op].y;
            }
            rot = op;
        }
        else {
            if (op == 'T') {
                if (carrying == true)
                    continue;
                if (valid_pickup(strt, moves[rot])) {
                    pii neww(strt.x + moves[rot].x, strt.y + moves[rot].y);
                    mat[neww.x][neww.y]--;
                    carrying = true;
                }
            } else {
                if (carrying == false)
                    continue;
                if (valid_lift(strt, moves[rot])) {
                    pii neww(strt.x + moves[rot].x, strt.y + moves[rot].y);
                    mat[neww.x][neww.y]++;
                    carrying = false;
                }
            }
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j <m; j++)
            cout << mat[i][j] <<" ";
        cout << "\n";
    }
}