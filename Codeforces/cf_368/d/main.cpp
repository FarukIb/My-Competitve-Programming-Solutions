#include <bits/stdc++.h>
 
using namespace std;
 
struct query {
  int type, i, j, next;
 
  query() {} 
  query(int _type, int i_, int j_, int nxt) {
    type = _type;
    next = nxt;
    i = i_;
    j = j_;
  }
 
  query(int _type, int nxt) {
    type = _type;
 
    next = nxt;
  }
 
  query(int _type, int i_, int nxt) {
    type = _type;
    i = i_;
    next = nxt;
  }
};
 
int n, m;
vector<vector<query> > graph;
vector<vector<bool> > mat;
 
vector<int> ans;
 
int dfs(int curr, int sum, query q) {
    bool done = false;
    if (q.type == 1) {
        if (!mat[q.i][q.j])
            mat[q.i][q.j] = true, sum++, done = true;
    }
    else if (q.type == 2) {
        if (mat[q.i][q.j])
            mat[q.i][q.j] = false, sum--, done = true;
    }
    else if (q.type == 3) {
        for (int i = 0; i < n; i++)
        {
            if (mat[i][q.i])
                sum--, mat[i][q.i] = false;
            else
                sum++, mat[i][q.i] = true;
        }
    }
 
    ans[curr] = sum;
 
    for (query x : graph[curr]) {
        dfs(x.next, sum, x);
    }
 
    if (q.type == 2 && done) {
        mat[q.i][q.j] = true, sum++, done = true;
    }
    else if (q.type == 1 && done) {
        mat[q.i][q.j] = false, sum--, done = true;
    }
    else if (q.type == 3) {
        for (int i = 0; i < n; i++)
        {
            if (mat[i][q.i])
                sum--, mat[i][q.i] = false;
            else
                sum++, mat[i][q.i] = true;
        }
    }
}
 
int main() {
    int q;
    cin >> m >> n >> q;
 
    graph.resize(q + 1, vector<query>());
    ans.resize(q + 1, 0);
    mat.resize(n + 1, vector<bool>(m + 1, false));
 
    for (int i = 1; i <= q; i++) {
        int type;
        cin >> type;
        if (type == 1 || type == 2) {
            int x, y;
            cin >> x >> y;
            x--, y--;
            graph[i - 1].push_back(query(type, y, x, i));
        }
        else if (type == 3) {
            int f;
            cin >> f;
            f--;
            graph[i - 1].push_back(query(type, f, i));
        }
        else {
            int k;
            cin >> k;
            graph[k].push_back(query(type, i));
        }
    }
    dfs(0, 0, query(4, 0));
 
    for (int i = 0; i < q; i++)
        cout << ans[i + 1] << "\n";
}
