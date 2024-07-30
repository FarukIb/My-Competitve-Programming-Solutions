#include <bits/stdc++.h>
#define mp make_pair
#define all(a) a.begin(), a.end()

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;
typedef pair<int, double> pid;

const double DINF = 1e18;
const ll INF = 1e18;
const double EPS = 1e-3;

vector<vector<pid> > graph;
vector<double> val;

double sum;
bool ok = false;
void dfs1(int curr) {
    if (!ok)
        return;
    for (auto &[a, d] : graph[curr]) {
        double new_v = d - val[curr];
        if (val[a] != DINF and abs(val[a] - new_v) > EPS)
        {
            ok = false;
            return;
        }
        if (val[a] != DINF)
            continue;
        val[a] = new_v; sum += abs(new_v);
        dfs1(a);
    }
}

vector<bool> visited;
vector<vector<int> > cmp;
void dfs2(int curr, vector<int> &cmp) {
    cmp.push_back(curr); visited[curr] = true;
    for (auto &[a, d] : graph[curr])
        if (!visited[a])
            dfs2(a, cmp);
}

ll tryy(int idx, double v, vector<int> &comp) {
    for (int a : comp)
        val[a] = DINF;
    val[idx] = v;
    sum = abs(v), ok = true;
    dfs1(idx);
    if (!ok)
        return INF;
    return sum;
}

pair<ll, double> get_for_cmp(int guy) {
    int cmp_size = cmp[guy].size(); pair<ll, double> mini(INF, 0);
    for (int val = -cmp_size*10; val <= cmp_size*10; val++)
        mini = min(mini, {tryy(guy, (double)val/2.0, cmp[guy]), (double)val/2.0});
    return mini;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int n, m;
    cin >>n >> m;
    graph.resize(n+1);
    val.resize(n+1);
    visited.resize(n+1);
    cmp.resize(n+1);

    for (int i = 0; i < m; i++) {
        int f, t, w;
        cin >> f >> t >> w;
        graph[f].push_back({t, w});
        graph[t].push_back({f, w});
    }
    // init_cmp
    for (int i = 1; i <= n; i++) {
        if (!visited[i]) {
            dfs2(i, cmp[i]);

            auto v = get_for_cmp(i);
            if (v.first == INF)
            {
                cout <<"NO\n";
                return 0;
            }
            tryy(i, v.second, cmp[i]);
        }
    }

    
    cout <<"YES\n";
    for (int i = 1; i <= n; i++)
        cout << val[i] << " ";
    cout << "\n";
}