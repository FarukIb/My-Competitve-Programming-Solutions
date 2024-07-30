#include <bits/stdc++.h>
#define mp make_pair

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

int n, m, k;
vector<vector<int> > graph;
vector<vector<int> > paths;

void dijkstra() {
    vector<int> mini(n + 1, 1e9);
    mini[0] = 0;

    priority_queue<pii> que;
    que.push(pii(0, 1));
    while (!que.empty()) {
        pii curr = que.top();

        for (int x : graph[curr.second]) {
            bool canMove = false, canStay = false;
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    cin >>n >> m;
    graph.resize(n + 1);
    for (int i = 0; i < m; i++) {
        int f, t;
        cin >> f >> t;
        graph[f].push_back(t);
        graph[t].push_back(f);
    }

    cin >> k;
    for (int i = 0; i < k; i++) {
        int siz;
        cin >> siz;
        vector<int> curr(siz);
        for (int j = 0; j < siz; j++)
            cin >> curr[j];
    }
}