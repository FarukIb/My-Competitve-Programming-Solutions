#include <bits/stdc++.h>
#define pii pair<int, int>
#define ll long long
#define ld long double

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int n;
    cin >> n;
    if (n % 2 == 0) { 
        cout << "NO\n";
        return 0;
    }
    else if (n == 1) {
        cout << "YES\n2 1\n2 1\n";
        return 0;
    }


    vector<pii> edges;
    for (int x = 0; x < n - 1; x++) {
        edges.push_back({0, x * n + 1});
        for (int i = 2; i <= n; i++)
        {
            edges.push_back({x * n + 1, x * n + i});
            if (x & 1) {
                for (int j = 2; j <= n; j++)
                    edges.push_back({x * n + i, (x - 1) * n + j});
            }
        }
    }
    edges.push_back(pii(0, (n - 1) * n + 1));
    int l = edges.size();
    for (int i = 0; i < l - 1; i++) {
        edges.push_back(pii(edges[i].first + (n - 1) * n + 1, edges[i].second + (n - 1) * n + 1));
    }

    cout << "YES\n";
    cout << edges[edges.size() - 1].first + 1 << " " << edges.size() << "\n";
    for (int i = 0; i < edges.size(); i++)
        cout << edges[i].first + 1 << " " << edges[i].second + 1 << "\n";
    
    /*map<int, int> deg;
    for (pii s : edges)
        deg[s.first]++, deg[s.second]++;
    
    cout << "\n";
    for (pii x : deg)
        cout << x.first + 1 << " " << x.second << "\n";*/
}
