#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <climits>
using namespace std;

int n, m, a, b;
vector<string> map;
vector<vector<int>> dis, pdis;
vector<pair<int,int>> dir = {{-1, 0}, {0, -1}, {1, 0}, {0, 1}}, ex;
vector<vector<pair<int,int>>> par;
queue<pair<int,int>> qu;

int main() {
    cin >> n >> m;
    map = vector<string>(n);
    dis = vector<vector<int>>(n, vector<int>(m, INT_MAX));
    pdis = vector<vector<int>>(n, vector<int>(m, INT_MAX));
    par = vector<vector<pair<int,int>>>(n, vector<pair<int,int>>(m, make_pair(-1, -1)));
    for(int i = 0; i < n; i++) {
        cin >> map[i];
        for(int j = 0; j < m; j++) {
            if(map[i][j] == 'A') {
                a = i;
                b = j;
                pdis[i][j] = 0;
            } else if(map[i][j] == 'M')  {
                qu.push(make_pair(i, j));
                dis[i][j] = 0;
            }
            if(map[i][j] != '#' && (i == 0 || i == n-1 || j == 0 || j == m-1)) ex.push_back(make_pair(i, j));
        }
    }
    while(qu.size()) {
        pair<int,int> c = qu.front();
        for(auto i : dir) {
            pair<int,int> pe = make_pair(c.first+i.first, c.second+i.second);
            if(pe.first < 0 || pe.first > n-1 || pe.second < 0 || pe.second > m-1) continue;
            if(dis[pe.first][pe.second] != INT_MAX || map[pe.first][pe.second] == '#') continue;
            dis[pe.first][pe.second] = dis[c.first][c.second]+1;
            qu.push(pe);
        }
        qu.pop();
    }
    while(qu.size()) qu.pop();
    qu.push(make_pair(a, b));
    while(qu.size()) {
        pair<int,int> c = qu.front();
        for(auto i : dir) {
            pair<int,int> pe = make_pair(c.first+i.first, c.second+i.second);
            if(pe.first < 0 || pe.first > n-1 || pe.second < 0 || pe.second > m-1) continue;
            if(pdis[pe.first][pe.second] != INT_MAX || map[pe.first][pe.second] == '#') continue;
            pdis[pe.first][pe.second] = pdis[c.first][c.second]+1;
            if(dis[pe.first][pe.second] <= pdis[pe.first][pe.second]) continue;
            par[pe.first][pe.second] = c;
            qu.push(pe);
        }
        qu.pop();
    }
    string res; bool ok = false;
    for(auto i : ex) {
        if (i == make_pair(a, b))
            ok = true;

        if(par[i.first][i.second] != make_pair(-1, -1)) {
            pair<int,int> pos = i, pr;
            ok = true;
            while(pos != make_pair(a, b)) {
                pr = par[pos.first][pos.second];
                if(pos.first+1 == pr.first) res+='U';
                else if(pos.first-1 == pr.first) res+='D';
                else if(pos.second+1 == pr.second) res+='L';
                else res+='R';
                pos = par[pos.first][pos.second];
            }
            reverse(res.begin(), res.end());
            break;
        }
    }
    if(ok) cout << "YES\n" << res.size() << "\n" << res << "\n";
    else cout << "NO\n";
}