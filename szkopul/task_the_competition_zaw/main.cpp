#include <bits/stdc++.h>
#define pii pair<ll, ll>
#define ll long long
#define ld long double

using namespace std;

int n, m;

vector<vector<pii> > graph1;
vector<vector<pii> > graph2;

vector<ll> dijkstra(vector<vector<pii> > &graph) {
    priority_queue<pii> que;
    que.push(pii(0, 1));

    vector<ll> dist(n + 1, 1e18);
    dist[1] = 0;

    while (!que.empty()) {
        pii curr = que.top();
        que.pop();

        for (pii x : graph[curr.second]) {
            if (dist[x.second] > curr.first + -x.first) {
                dist[x.second] = curr.first + -x.first;
                que.push(pii(-dist[x.second], x.second));
            }
        }
    }

    return dist;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    cin >> n >> m;
    graph1.resize(n + 1, vector<pii>());
    graph2.resize(n + 1, vector<pii>());

    for (int i = 0; i < m; i++) {
        int a, b, c, d;
        cin >> a >> b >> c >> d;

        graph1[a].push_back(pii(b, c));
        graph1[b].push_back(pii(a, d));

        graph2[a].push_back(pii(b, d));
        graph2[b].push_back(pii(a, b));
    }

    vector<ll> dist1 = dijkstra(graph1);
    vector<ll> dist2 = dijkstra(graph2);

    ll out = 1e18;
    for (int i = 2; i <= )
}
