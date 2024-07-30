#include <bits/stdc++.h>
#define mp make_pair
#define all(a) a.begin(), a.end()

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

vector<vector<int> > graph;
vector<int> coloring;
void citavu_lozu_isprazni(int curr, int forbid, vector<int> &cols) {
    
}

bool brute(int curr, int k, vector<int> &cols, int left) {
    if (!coloring.empty())
        return true;

    for (int a : graph[curr]) {
        if (cols[a] == cols[curr])
            return false;
        if (cols[a] != 0)
            continue;
        for (int i = 1; i <= k; i++)
        {
            cols[a] = i;
            if (brute(a, k, cols, left - 1))
                break;
            cols[a] = 0;
        }
        if (cols[a] == 0)
            return false;
    }
    if (left == 0)
        coloring = cols;
    return true;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    freopen("input_000.txt", "r", stdin);
    freopen("output_000.txt", "w", stdout);

    int n, m;
    cin >> n >> m;
    graph.resize(n + 1);
    for (int i = 0; i < m; i++)
    {
        int f, t;
        cin >> f >> t;
        graph[f].push_back(t);
        graph[t].push_back(f);
    }

    int l = 1, r = n + 1; vector<int> ans;
    while (l < r) {
        int mid = (l + r) / 2;
        coloring.clear();
        vector<int> neww(n+1);
        neww[1] = 1;
        brute(1, mid, neww, n - 1);
        if (coloring.empty())
            l = mid + 1;
        else
            r = mid, ans = coloring;
    }

    cout << *max_element(all(coloring)) << "\n";
    for (int i = 0; i < n; i++)
        cout << coloring[i + 1] << " ";
    cout << "\n";
}