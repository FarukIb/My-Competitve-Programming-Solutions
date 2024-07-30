#include <bits/stdc++.h>
#define mp make_pair
#define all(a) a.begin(), a.end()

using namespace std;

typedef long long ll;
typedef pair<ll, ll> pii;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int n, m;
    cin >> n >> m;
    vector<vector<pii> > graph((n + 1)* 2);
    for (int i = 0; i < m; i++) {
        int f, t, w;
        cin >> f >> t >> w;
        graph[f].push_back({t, w});

        graph[f + n].push_back({t+n, w});

        graph[f].push_back({t+n, w/2});
    }

    vector<ll> dist((n + 1)*2, 1e18);
    dist[1] = 0;
    priority_queue<pii, vector<pii>, greater<pii>> q; q.push({0, 1});
    while (!q.empty()) {
        pii c = q.top(); q.pop(); int curr = c.second;
        if (dist[curr] != c.first)
            continue;
        for (pii e : graph[c.second]) {
            if (dist[e.first] > dist[curr] + e.second) {
                dist[e.first] = dist[curr] + e.second;
                q.push({dist[e.first], e.first});
            }
        }
    }

    cout << dist[2 * n] << "\n";
}