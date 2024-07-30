#include <bits/stdc++.h>
#define mp make_pair
#define all(a) a.begin(), a.end()

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

string mat[8];
int out(int i, int j, vector<pii> pos, int num) {
    if (num == 8)
        return 1;
    if (i == 8)
        return 0;
    bool can_place = true;
    for (auto &[x, y] : pos)
        if (x == i || y == j || x + y == i + j || x - y == i - j)
            can_place = false;
    if (mat[i][j] == '*')
        can_place = false;
    int ni = i, nj = j;
    nj++;
    if (nj == 8)
        ni++, nj = 0;
    ll ret = out(ni, nj, pos, num);
    if (can_place) {
        pos.push_back({i, j});
        ret += out(i+1, 0, pos, num + 1);
    }
    
    return ret;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    for (int i = 0; i < 8; i++)
        cin >> mat[i];
    cout << out(0, 0, {}, 0) << "\n";
}