#include <bits/stdc++.h>
#define mp make_pair
#define all(a) a.begin(), a.end()

using namespace std;

typedef long long ll;
typedef pair<ll, ll> pii;

vector<vector<pii> > graph; int n;
vector<ll> dijkstra(int p) {
    vector<ll> dist(n, 1e18);
    dist[p] = 0;
    priority_queue<pii, vector<pii>, greater<pii> > qu;
    qu.push({(ll)0, p});
    while (!qu.empty()) {
        pii curr = qu.top(); qu.pop();
        if (curr.first > dist[curr.second])
            continue;
        for (auto &[t, w] : graph[curr.second]) {
            if (dist[t] > curr.first + w) {
                dist[t] = curr.first + w;
                qu.push({dist[t], t});
            }
        }
    }
    return dist;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int m, q;
    cin >> n >> m >> q;
    graph.resize(n);
    for (int i = 0; i < m; i++) {
        ll f,t ,w;
        cin >>f >> t >> w;
        graph[f].push_back({t, w});
        graph[t].push_back({f, w});
    }
    vector<ll> dists = dijkstra(q);
    for (auto a : dists)
        cout << a << "\n";
}