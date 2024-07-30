#include <bits/stdc++.h>
#define mp make_pair
#define all(a) a.begin(), a.end()

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

int n;
vector<vector<int> > graph;
vector<ll> val;
vector<ll> dp_chain;
vector<ll> dpn;

void dfs(int curr, int par) {
    dp_chain[curr] = max(0, val[curr]);
    dpn[curr] = val[curr];
    for (int a : graph[curr])
    {
        dfs(a, curr);
        dp_chain[curr] = max(dp_chain[curr], dp_chain[a]);
        for ()
    }
    
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int t;
    cin >> t;
    while (t--) {
        cin >> n;
        graph = vector<vector<int> > (n + 1);
        val = vector<ll> (n + 1);
        for (int i = 1; i <= n; i++)
            cin >> val[i];
        
        int max_deg = 0;
        for (int i = 1; i <= n; i++)
            max_deg = max(max_deg, (int)graph[i].size());
        if (max_deg == 2) {
            sort(all(val));
            cout << max(0LL, val.back()) + max(0LL, *prev(prev(val.end()))) << "\n";
            continue;
        }

        dp_chain = dpn = vector<ll> (n + 1);
    }
}