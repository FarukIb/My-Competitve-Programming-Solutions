#include <bits/stdc++.h>
#define pii pair<int, int>
#define ll long long
#define ld long double

using namespace std;

vector<vector<int> > graph;
vector<int> par;

set<int> visited;
vector<int> stck;
void topo(int x) {
    if (visited.count(x))
        return;

    visited.insert(x);
    for (int s : graph[x])
        topo(s);
    stck.push_back(x);
}

vector<int> order;
vector<int> leftest;
void dfs(int x, pii lftst) {
    visited.insert(x);
    lftst = min(lftst, pii(order[x], x));
    leftest[x] = lftst.second;
    
    for (int s : graph[x])
        dfs(s, lftst);
    
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int n, m;
    cin >> n >> m;
    graph.resize(n + 1, vector<int>());
    par.resize(n + 1, 0);

    for (int i = 0; i < m; i++) {
        int p, c;
        cin >> p >> c;

        par[c] = p;
        graph[p].push_back(c);
    }

    // TOPO SORT
    for (int i = 1; i <= n; i++)
        if (!visited.count(i))
            topo(i);
    order.resize(n + 1);
    //reverse(stck.begin(), stck.end());
    for (int i = 0; i < n; i++)
        order[stck[i]] = i; 

    vector<pii> lst(n);
    vector<int> og(n);
    leftest.resize(n + 1, 1e9);
    for (int i = 0; i < n; i++) {
        cin >> lst[i].second;
        og[i] = lst[i].second;
        lst[i].first = order[lst[i].second];
    }
    sort(lst.begin(), lst.end());
    fill(order.begin(), order.end(), 1e9);
    for (int i = n - 1; i >= 0; i--)
        order[lst[i].second] = i;
    visited.clear();

    // CHECKING

    for (int i = 1; i <= n; i++) {
        if (visited.count(i))
            continue;
        int curr = i;
        while (par[curr] != 0) {
            curr = par[curr];
        }

        dfs(curr, pii(order[curr],curr));
    }

    bool good = true;
    for (int i = 1; i <= n; i++)
        if (leftest[i] != og[i - 1])
            good = false;

    if (!good)
        cout << "-1\n";
    else
    {
        vector<int> neww;
        vector<bool> there(n + 1, false);
        for (int i = 0; i < n; i++)
        {
            if (there[lst[i].second] == false)
            {
                there[lst[i].second] = true;
                neww.push_back(lst[i].second);
            }
        }

        cout << neww.size() << "\n";
        for (int i : neww)
            cout << i << "\n";
    }
}
