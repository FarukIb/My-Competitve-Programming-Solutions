#include <bits/stdc++.h>
#define mp make_pair
#define all(a) a.begin(), a.end()

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

const int K = 20;

vector<int> in_time;
vector<int> out_time;
vector<int> h;
vector<vector<int> > pars;

bool is_ancestor(int a, int b) { // a is par
    return in_time[a] <= in_time[b] and out_time[b] <= out_time[a];
}

int lca(int a, int b) {
    if (h[a] > h[b])
        swap(a, b);
    if (is_ancestor(a, b))
        return a;
    for (int i = K - 1; i >= 0; i--) {
        if (!is_ancestor(pars[a][i], b))
            a = pars[a][i];
    }
    return pars[a][0];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int n, q;
    cin >> n >> q;
    vector<vector<int> > graph(n+1);
    pars.resize(n + 1, vector<int>(K, 0));
    for (int i = 2; i <= n; i++)
    {
        cin >> pars[i][0];
        graph[pars[i][0]].push_back(i);
    }

    in_time.resize(n + 1);
    out_time.resize(n + 1); out_time[0] = 1e9;
    h.resize(n+1, -1);
    function<void(int)> dfs; int time = 0;
    dfs = [&](int curr) {
        in_time[curr] = time;
        for (int i = 1; i < K; i++)
            pars[curr][i] = pars[pars[curr][i - 1]][i - 1];
        h[curr] = h[pars[curr][0]] + 1;
        for (int a : graph[curr]) {
            time++;
            dfs(a);
        }
        out_time[curr] = time;
    };
    dfs(1);

    while (q--) {
        int a, b;
        cin >> a >> b;
        cout << lca(a, b) << "\n";
    }
}