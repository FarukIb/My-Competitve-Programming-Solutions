#include <bits/stdc++.h>
#define mp make_pair
#define all(a) a.begin(), a.end()

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

const int K = 20;
const int INF =  1e9;

vector<vector<int> > graph;
int n, m;
vector<int> dist(int f) {
    vector<int> dist(n+1, INF);
    dist[f] = 0;
    queue<int> q;
    q.push(f);
    while (!q.empty()) {
        int a = q.front(); q.pop();
        for (int nei : graph[a]) {
            if (dist[nei] == INF) {
                dist[nei] = dist[a] + 1;
                q.push(nei);
            }
        }
    }
    return dist;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    srand(time(0));
    int p;
    cin >> n >> m >> p;
    graph.resize(n+1);
    for (int i = 0; i < m; i++) {
        int f, t;
        cin >> f >>t;
        graph[f].push_back(t);
        graph[t].push_back(f);
    }

    vector<int> ans(p, 1e9);
    vector<pii> quers(p);
    for (int i = 0; i < p; i++) 
        cin >> quers[i].first >> quers[i].second;
    for (int O = 0; O < 150; O++) {
        int node = rand() % n + 1;
        vector<int> ds = dist(node);
        for (int i = 0; i < p; i++)
            ans[i] = min(ans[i], ds[quers[i].first] + ds[quers[i].second]);
    }

    for (int a: ans)
        cout <<a << "\n";
}