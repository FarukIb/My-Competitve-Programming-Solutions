#include <bits/stdc++.h>
#define pii pair<ll, ll>
#define ll long long
#define ld long double
#define mp make_pair

using namespace std;

ll num_nodes, n, m, k;
ll strt, endd;

vector<vector<pii> > graph;

ll dijkstra() {
    priority_queue<pii> que;
    que.push(mp(0, strt));

    vector<ll> dist(num_nodes, 1e18);
    dist[strt] = 0;
    while (!que.empty()) {
        pii curr = que.top();
        que.pop();

        for (pii x : graph[curr.second]) {
            if (dist[x.first] > -curr.first + x.second) {
                dist[x.first] = -curr.first + x.second;
                que.push(pii(-dist[x.first], x.first));
            }
        }
    }

    return min(dist[endd], dist[endd + num_nodes / 2]);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    cin >> n >> m >> k;

    vector<pii> switches(k);
    for (ll i = 0; i < k; i++)
        cin >> switches[i].first >> switches[i].second;
    
    // finding start and end
    strt = -1;
    for (ll i = 0; i < k; i++)
        if (switches[i].first == 1 && switches[i].second == 1) 
            strt = i;
    if (strt == -1)
        strt = k, k++;
    
    endd = -1;
    for (ll i = 0; i < k; i++)
        if (switches[i].first == n && switches[i].second == m)
            endd = i;
    if (endd == -1)
        endd = k, k++;
    
    num_nodes = 2 * k;

    // making graph
    graph.resize(num_nodes, vector<pii>());
    
    vector<pair<pii, ll> > xy;
    for (ll i = 0; i < switches.size(); i++)
        xy.push_back(mp(switches[i], i));
    if (strt >= switches.size())
        xy.push_back(mp(mp(1, 1), strt));
    if (endd >= switches.size())
        xy.push_back(mp(mp(n, m), endd));

    sort(xy.begin(), xy.end());
    for (ll i = 0; i < xy.size(); i++) {
        if (i != 0 && xy[i].first.first == xy[i - 1].first.first)
            graph[xy[i].second].push_back(mp(xy[i - 1].second, xy[i].first.second - xy[i - 1].first.second));
        if (i != xy.size() - 1 && xy[i].first.first == xy[i + 1].first.first)
            graph[xy[i].second].push_back(mp(xy[i + 1].second, xy[i + 1].first.second - xy[i].first.second));
    }

    vector<pair<pii, ll> > yx;
    for (ll i = 0; i < switches.size(); i++)
        yx.push_back(
            mp(
            mp(switches[i].second, switches[i].first),
             num_nodes / 2 + i));
    if (strt >= switches.size())
        yx.push_back(mp(mp(1, 1), strt + num_nodes / 2));
    if (endd >= switches.size())
        yx.push_back(mp(mp(m, n), endd + num_nodes / 2));
    sort(yx.begin(), yx.end());
    for (ll i = 0; i < yx.size(); i++) {
        if (i != 0 && yx[i].first.first == yx[i - 1].first.first)
            graph[yx[i].second].push_back(mp(yx[i - 1].second, yx[i].first.second - yx[i - 1].first.second));
        if (i != yx.size() - 1 && yx[i].first.first == yx[i + 1].first.first)
            graph[yx[i].second].push_back(mp(yx[i + 1].second, yx[i + 1].first.second - yx[i].first.second));
    }

    // adding bridges :)
    for (ll i = 0; i < switches.size(); i++)
        graph[i].push_back(pii(i + num_nodes / 2, 1)), graph[i + num_nodes / 2].push_back(mp(i, 1));
    

    ll out = dijkstra();
    if (out == 1e18)
        cout << "-1\n";
    else
        cout << out << "\n";
}
