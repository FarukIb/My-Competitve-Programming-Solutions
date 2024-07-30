#include <bits/stdc++.h>
#define mp make_pair
#define all(a) a.begin(), a.end()

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

const ll INF = 1e14;

int n;

struct edge {
    int idx;
    ll cap, cost, f, t;
};

ll cost(edge &e) {
    
}

vector<vector<ll> > cap, cost, graph;

void add_edge(int f, int t, ll cp, ll cst) {
    cap[f][t] = cp;
    cost[f][t] = cst;
    cost[t][f] = -cst;
    graph[f].push_back(t);
    graph[t].push_back(f);
}

int num_nodes;
vector<ll> par, dist;

void shortest_path(int f) {
    fill(all(dist), INF);
    dist[f] = 0;
    vector<bool> inq(num_nodes);
    inq[f] = true;
    queue<int> q; q.push(f);
    while (!q.empty()) {
        int c = q.front(); q.pop();
        inq[c] = false;
        for (int nei : graph[c]) {
            if (cap[c][nei] != 0 and dist[nei] > dist[c] + cost[c][nei]) {
                dist[nei] = dist[c] + cost[c][nei];
                par[nei] = c;
                if (!inq[nei]) {
                    inq[nei] = true;
                    q.push(nei);
                }
            }
        }
    }
}

ll min_cost_flow(int s, int t) {
    par = dist = vector<ll> (num_nodes);
    ll cst = 0;
    while (1) {
        shortest_path(s);
        if (dist[t] == INF)
            break;
        ll f = INF;
        ll curr = t;
        while (curr != s) {
            f = min(f, cap[par[curr]][curr]);
            curr = par[curr];
        }

        cst += f * dist[t];
        curr = t;
        while (curr != s) {
            cap[par[curr]][curr] -= f;
            cap[curr][par[curr]] += f;
            curr = par[curr];
        }
    }
    return cst;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int k;
    cin >> n >> k;
    num_nodes = 2 * n + 3; 
    int s = 0, t = 2 * n + 1;
    int lnk = 2 * n + 2;
    graph = vector<vector<ll> > (num_nodes);
    cap = vector<vector<ll> > (num_nodes, vector<ll>(num_nodes, 0));
    cost = vector<vector<ll> > (num_nodes, vector<ll> (num_nodes));
    vector<pii> orders(n + 1);
    add_edge(s, lnk, k, 0);
    for (int i = 1; i <= n; i++)
    {
        add_edge(lnk, i, 1, 0);
        add_edge(i + n, t, 1, 0);
        add_edge(i, i + n, 1, -INF);
        cin >> orders[i].first >> orders[i].second;
    }

    for (int i = 1; i <= n; i++)
        for (int j = i + 1; j <= n; j++)
            add_edge(i + n, j, 1, abs(orders[i].second - orders[j].first));
    
    cout << min_cost_flow(s, t) + INF * n << "\n";
}