#include <bits/stdc++.h>
#define mp make_pair
#define all(a) a.begin(), a.end()

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

int n;
vector<vector<int> > graph;
vector<int> subtree_size;
vector<int> centroids;
void subt(int curr, int par) {
    for (int a : graph[curr])
        if (a != par)
            subt(a, curr), subtree_size[curr] += subtree_size[a];
}

int find_centr(int curr, int par) {
    for (int a : graph[curr])
        if (a != par)
            if (subtree_size[a] * 2 > n)
                return find_centr(a, curr);
    return curr;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    cin >> n;
    subtree_size.resize(n+1, 1);
    graph.resize(n + 1);
    for (int i = 1; i < n; i++) {
        int a, b;
        cin >> a >>b;
        graph[a].push_back(b);
        graph[b].push_back(a);
    }

    subt(1, 0);
    cout <<find_centr(1, 0) << "\n";
}