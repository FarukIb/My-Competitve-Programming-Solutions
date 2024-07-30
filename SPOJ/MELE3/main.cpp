#include <bits/stdc++.h>
#define pii pair<int, int>

using namespace std;

int getTime(int bottom, int top, int where, int passed) {
    passed %= ((top - bottom) * 2);

    where -= bottom, top -= bottom, bottom = 0;

    if (where == bottom) {
        if (passed == 0)
            return 0;
        return (top - bottom) * 2 - passed;
    }
    else {
        if (passed == top)
            return 0;
        
        if (passed < top)
            return top - passed;
        else
            return (top - bottom) * 2 - passed + top;
    }
}

int k, n;
vector<vector<int> > graph;
int dijkstra() {
    vector<int> dist(k + 1, (int)1e9);
    dist[1] = 0;

    priority_queue<pii> que;
    que.push(pii(0, 1)); // FIRST == TIME, SECOND == NODE
    while (!que.empty()) {
        pii curr = que.top(); que.pop();

        for (int x : graph[curr.second]) {
            int overallTime = 0;
            
            int bottom = curr.second, top = x, where;
            if (bottom > top)
            {
                swap(bottom, top);
                where = top;
            }
            else
                where = bottom;
            overallTime = getTime(bottom, top, where, curr.first) + top - bottom;


            if (curr.first + overallTime < dist[x]) {
                dist[x] = curr.first + overallTime;
                que.push(pii(dist[x], x));
            }
        }
    }

    return dist[k];
}

int main() {
    cin >> k >> n;
    graph.resize(k + 1);
    for (int i = 0; i < n; i++) {
        int f, t;
        cin >> f >> t;
        graph[f].push_back(t);
        graph[t].push_back(f);
    }

    cout << dijkstra() * 5 << "\n";
}