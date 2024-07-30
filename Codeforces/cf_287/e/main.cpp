#include <bits/stdc++.h>
#define mp make_pair

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int n, m, o = 0;
    cin >> n >> m;
    vector<vector<pii> > graph(n + 1);

    map<pii, pii> edges;
    for (int i = 0; i < m; i++) {
        int f, t, x;
        cin >> f >> t >> x;
        if (x == 1)
            o++;
        
        if (f > t)
            edges[minmax(f, t)] = pii(x, 1);
        else
            edges[minmax(f, t)] = pii(x, 0);
        graph[f].push_back(pii(t, x));
        graph[t].push_back(pii(f, x));
    }

    vector<int> shortest(n + 1, 1e9);
    shortest[0] = 0;
    queue<pii> que;
    que.push(pii(1, 0));
    while (!que.empty()) {
        int curr = que.front().first;
        shortest[curr] = que.front().second;
        que.pop();

        for (pii s : graph[curr]) {
            if (shortest[s.first] == 1e9) {
                shortest[s.first] = shortest[curr] + 1;
                que.push(pii(s.first, shortest[curr] + 1));
            }
        }
    }

    vector<int> dp(n + 1, 1e9);
    vector<int> par(n + 1, -1);
    dp[1] = 0;
    que.push(pii(1, 0));
    while (!que.empty()) {
        int curr = que.front().first;
        que.pop();

        for (pii s : graph[curr]) {
            if (shortest[curr] >= shortest[s.first])
                continue;

            if (dp[s.first] == 1e9) {
                dp[s.first] = dp[curr] + (1 - s.second);
                par[s.first] = curr;
                que.push(pii(s.first, dp[s.first]));
            } else if (dp[s.first] > dp[curr] + (1 - s.second)) {
                dp[s.first] = dp[curr] + (1 - s.second);       
                par[s.first] = curr;
            }
        }
    }

    set<pii> path;
    int curr = par[n], last = n;
    while (curr != -1) {
        path.insert(minmax(curr, last));

        last = curr;
        curr = par[curr];
    }

    int num = 2 * dp[n] + o - shortest[n];
    cout << num << "\n";
    for (pair<pii, pii> edge : edges) {
        pii state = edge.second;
        if (state.first == 1 && path.count(edge.first) || state.first == 0 && !path.count(edge.first))
            continue;

        cout << edge.first.first << " " << edge.first.second << " " << 1 - state.first << "\n";
    }
}