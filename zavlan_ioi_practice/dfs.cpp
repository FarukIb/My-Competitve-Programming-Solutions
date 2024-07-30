#include <bits/stdc++.h>
#define mp make_pair
#define all(a) a.begin(), a.end()

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

vector<vector<int> > graph;
vector<int> par;
vector<int> depth;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int n;
    cin >> n;
    graph.resize(n);
    par.resize(n, -1);
    depth.resize(n);
    for (int i = 1; i < n; i++) {
        cin >> par[i];
        graph[i].push_back(par[i]);
        graph[par[i]].push_back(i);
    }
    
    stack<int> stc;
    stc.push(0);
    while (!stc.empty()) {
        int curr =stc.top(); stc.pop();
        for (int a : graph[curr]) {
            if (a != par[curr]) {
                stc.push(a);
                depth[a] = depth[curr] + 1;
            }
        }
    }

    int idx = max_element(all(depth)) - depth.begin();
    vector<int> path;
    path.push_back(idx);
    while (idx != 0) {
        idx = par[idx];
        path.push_back(idx);
    }
    reverse(all(path));
    for (int a : path)
        cout << a << "\n";
}