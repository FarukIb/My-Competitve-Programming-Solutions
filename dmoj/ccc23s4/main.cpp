#include <bits/stdc++.h>
#define mp make_pair
#define all(a) a.begin(), a.end()

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

struct UFDS {
    vector<int> ufds;
 
    UFDS(int S) {
        ufds.resize(S + 1);
        for (int i = 0; i <= S; i++)
            ufds[i] = i;
    }
 
    int find(int x) {
        if (ufds[x] == x)
            return x;
        return ufds[x] = find(ufds[x]);
    }
 
    void merge(int x, int y) {
        if (find(x) == find(y))
            return;
        ufds[find(x)] = find(y);
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int n, m;
    cin >> n >> m;
    priority_queue<pair<ll, pii>, vector<pair<ll, pii> >, greater<pair<ll, pii> > > edges;
    for (int i = 0; i < m; i++) {
        int f, t, a, b;
        cin >> f >> t >> a >> b;
        edges.push({b, {f, t}});
    }

    ll cost = 0;
    UFDS ufds(n +1);
    while (!edges.empty()) {
        auto curr = edges.top(); edges.pop();
        if (ufds.find(curr.second.first) == ufds.find(curr.second.second))
            continue;
        cost += curr.first;
        ufds.merge(curr.second.first, curr.second.second);
    }

    cout << cost << "\n";
}