#include <bits/stdc++.h>
#define mp make_pair
#define all(a) a.begin(), a.end()

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int n, m;
    cin >> n >> m;
    vector<vector<pii> > graph(n+1);
    vector<int> perm(n);
    for (int i = 0; i < m; i++) {
        int f, t;
        cin >> f >> t;
        graph[f].push_back({t, i});
        graph[t].push_back({f, i});
    }
    vector<int> par(n + 1);
    vector<bool> visited(n+1);
    vector<int> dist(n + 1);    
    vector<bool> done(m);
    int mini = 1e9;
    for (int s = 1; s <= n; s++) {
        for (pii e : graph[s]) {
            if (done[e.second] || mini == 3)
                continue;
            done[e.second] = true;
            queue<int> que;
            que.push(e.first);
            fill(all(par), 0);
            fill(all(visited), false);
            dist[e.first] = 0;
            
            while (que.size()) {
                int curr = que.front(); que.pop();
                if (dist[curr] >= mini)
                    break;
                visited[curr] = true;
                if (curr == s) {
                    mini = min(mini, dist[curr] + 1);
                    break;
                }
                for (pii a : graph[curr]) {
                    if (a.second == e.second || visited[a.first])
                        continue;
                    dist[a.first] = dist[curr] + 1;
                    que.push(a.first);
                }
            }
        }
    }

    if (mini == 1e9)
        cout << "-1\n";
    else
        cout << mini << "\n";
}