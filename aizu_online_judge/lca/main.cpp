#include <bits/stdc++.h>
#define pii pair<int, int>
#define ll long long
#define ld long double

using namespace std;

struct seggy {
    vector<pii> t;
    int n;

    seggy(vector<pii> arr) {
        n = arr.size();
        t.resize(n * 2);
        for (int i = 0; i < n; i++)
            t[i + n] = arr[i];
        for (int i = n - 1; i > 0; i--) 
            t[i] = min(t[i * 2], t[i * 2 + 1]);
    }

    int query(int l, int r) {
        pii out(1e9, 1e9);
        for (l += n, r += n + 1; l < r; l /= 2, r /= 2) {
            if (l & 1)
                out = min(out, t[l++]);
            if (r & 1)
                out = min(out, t[--r]);
        }
        return out.second;
    }
};

vector<vector<int> > graph;
vector<pii> tour;
vector<int> ent;
vector<int> leav;
void dfs(int curr, int hght = 0, int par = -1) {
    ent[curr] = tour.size();
    tour.push_back(pii(hght, curr));
    for (int x : graph[curr])
    {
        if (x != par)
        {
            dfs(x, hght + 1, curr);
            leav[curr] = tour.size();
            tour.push_back({hght, curr});
        }
    }
    if (leav[curr] == -1)    
        leav[curr] = ent[curr];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int n;
    cin >> n;
    graph.resize(n);
    ent.resize(n);
    leav.resize(n, -1);

    for (int i = 0; i < n; i++) {
        int k;
        cin >> k;
        for (int j = 0; j < k; j++) {
            int s;
            cin >> s;
            graph[s].push_back(i);
            graph[i].push_back(s);
        }
    }

    dfs(0);
    seggy seg(tour);
    int q;
    cin >> q;
    while (q--) {
        int u, v;
        cin >> u >> v;
        cout << seg.query(minmax(leav[u], ent[v]).first, minmax(leav[u], ent[v]).second) << "\n";
    }
}
