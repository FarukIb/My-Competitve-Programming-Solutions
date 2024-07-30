#include <bits/stdc++.h>
#define mp make_pair
#define all(a) a.begin(), a.end()

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

const ll INF = 1e18;

vector<vector<ll> > capacity, graph, cost;

void add_edge(int f, int t, int cst, int cap) {
    graph[f].push_back(t);
    graph[t].push_back(f);
    capacity[f][t] = cap;
    cost[f][t] = cst;
    cost[t][f] = -cst;
}

int num_nodes;
vector<ll> dist, par;
void find_path(int f) {
    fill(all(dist), INF);
    queue<int> q;
    q.push(f);
    vector<bool> in_q(num_nodes + 1);
    dist[f] = 0;
    in_q[f] = true;
    while (!q.empty()) {
        int c = q.front(); q.pop();
        in_q[c] = false;
        for (ll to : graph[c]) {
            if (dist[to] > dist[c] + cost[c][to] and capacity[c][to] > 0) {
                dist[to] = dist[c] + cost[c][to];
                par[to] = c;
                if (!in_q[to])
                    q.push(to), in_q[to] = true;
            }
        }
    }
}

ll find_flow(int s, int t, int k) {
    dist = vector<ll> (num_nodes + 1);
    par = vector<ll> (num_nodes + 1);

    ll flow = 0, cst = 0;
    while (1) {
        find_path(s);
        if (dist[t] == INF)
            break;
        ll f = k - flow;
        int cur = t;
        while (cur != s) {
            f = min(f, capacity[par[cur]][cur]);
            cur = par[cur];
        }

        flow += f;
        cst += f * dist[t];
        cur = t;
        while (cur != s) {
            capacity[par[cur]][cur] -= f;
            capacity[cur][par[cur]] += f;
            cur = par[cur];
        }
    }
    return cst;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int n;
    cin >> n;
    num_nodes = 2 * n + 2;
    int s = 0, t = 2 * n + 1;
    graph = vector<vector<ll> >(num_nodes);
    capacity = vector<vector<ll> > (num_nodes, vector<ll> (num_nodes, 0));
    cost = vector<vector<ll> > (num_nodes, vector<ll> (num_nodes, INF));
    for (int i = 1; i <= n; i++) {
        add_edge(s, i, 0, 1);
        add_edge(i + n, t, 0, 1);
        for (int j = n + 1; j <= n * 2; j++) {
            cin >> cost[i][j];
            add_edge(i, j, cost[i][j], 1);
        }
    }

    cout << find_flow(s, t, n) << "\n";
    for (int i = 1; i <= n; i++)
        for (int j = n + 1; j <= n * 2; j++)
            if (capacity[i][j] == 0) 
                cout << i << " " << j - n << "\n";
}