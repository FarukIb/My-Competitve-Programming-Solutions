#include <bits/stdc++.h>
#define mp make_pair

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

const int bits = 20;

vector<vector<int> > graph;
vector<vector<int> > par;
int n;

void make_par() {
    for (int i = 0; i < bits; i++)
        par[0].push_back(0);
    par[1].push_back(0);
    for (int bit = 1; bit < bits; bit++)
    {
        for (int i = 1; i <= n; i++)    
        {
            par[i].push_back(par[par[i][bit - 1]][bit - 1]);
        }
    }
}

vector<int> enter_time;
vector<int> exit_time;
int tim = 0;
void dfs(int curr) {
    enter_time[curr] = tim;
    tim++;
    for (int neighb : graph[curr])
    {
        if (par[curr].empty() || neighb != par[curr][0])
        {
            par[neighb].push_back(curr);
            dfs(neighb);
        }
    }
    exit_time[curr] = tim;
}

bool is_ancestor(int par, int child) {
    return enter_time[par] <= enter_time[child] && exit_time[par] >= exit_time[child];
}

int LCA(int a, int b) {
    if (is_ancestor(a, b))
        return a;
    if (is_ancestor(b, a))
        return b;

    int curr = a;
    for (int c = bits - 1; c >= 0; c--) {
        int guy = par[curr][c];
        if (is_ancestor(guy, a) and is_ancestor(guy, b))
            continue;
        curr = guy;
    }
    return par[curr][0];
}

vector<int> sum;

void dfs_sum(int curr, vector<int> &translation, vector<int> &cnt) {
    for (int s : graph[curr]) {
        if (s == par[curr][0])
            continue;
        dfs_sum(s, translation, cnt);
        sum[curr] += sum[s];
    }
    if (curr == 1)
        return;
    cnt[translation[curr]] = sum[curr];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    cin >> n;
    sum.resize(n + 1, 0);
    enter_time.resize(n + 1);
    enter_time[0] = -1;
    exit_time.resize(n + 1);
    exit_time[0] = 1e9;
    graph.resize(n + 1);
    par.resize(n + 1);

    vector<pii> edges;
    for (int i = 1; i < n; i++) {
        int f, t;
        cin >> f >>t;
        edges.push_back(mp(f, t));
        graph[f].push_back(t);
        graph[t].push_back(f);
    }

    dfs(1);
    make_par();

    vector<int> cnt(n, 0);
    vector<int> translation(n + 1);
    for (int i = 0; i < n - 1; i++) {
        pii curr =edges[i];
        if (is_ancestor(curr.first, curr.second))
            swap(curr.first, curr.second);
        translation[curr.first] = i;
    }

    int q;
    cin >> q;
    while (q--) {
        int f, t;
        cin >> f >> t;
        int lca = LCA(f, t);
        sum[f]++;
        sum[t]++;
        sum[lca] -= 2;
    }

    dfs_sum(1, translation, cnt);
    for (int i = 0; i < n - 1; i++)
        cout << cnt[i] << " ";
    cout << "\n";
}