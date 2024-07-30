#include <bits/stdc++.h>
#define mp make_pair

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

vector<vector<int> > graph;
vector<int> cols;
vector<set<int> > sets;
void ans(int curr, int par) {
    for (int s : graph[curr]) {
        if (s == par)
            continue;
        ans(s, curr);
        if (sets[s].size() > sets[curr].size())
            sets[s].swap(sets[curr]);
        for (int x : sets[s])
            sets[curr].insert(x);
    }
    cols[curr] = sets[curr].size();
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int n;
    cin >> n;
    graph.resize(n + 1);
    cols.resize(n + 1);
    sets.resize(n + 1);
    for (int i = 1; i <= n; i++)
    {
        int s;
        cin >> s;
        sets[i].insert(s);
    }
    for (int i = 1; i < n; i++) {
        int f, t;
        cin >> f >> t;
        graph[f].push_back(t);
        graph[t].push_back(f);
    }
    ans(1, 0);
    for (int i = 1; i <= n; i++)
        cout << cols[i] << " ";
    cout << "\n";
}