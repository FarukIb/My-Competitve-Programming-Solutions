#include <bits/stdc++.h>
#define pii pair<int, int>
#define ll long long
#define ld long double

using namespace std;

int query(vector<int> query) {
    cout << "? 3";
    for (int x : query)
        cout << " " << x;
    cout << endl;

    int s;
    cin >> s;
    return s;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int T;
    cin >> T;
    while (T--) {
        int n;
        cin >> n;
        
        vector<set<int> > parents(n + 1, set<int>());
        for (int i = 2; i <= n; i++) {
            for (int j = 2; j <= n; j++) {
                if (i == j)
                    continue;
                if (query(vector<int>({1, i, j})))
                {
                    parents[j].insert(i);
                    parents[i].insert(1);
                }
                
            }
        }

        vector<pii> edges;
        for (int i = 2; i <= n; i++) {
            int par = 1;
            for (int x : parents[i])
                if (parents[x].size() > parents[par].size())
                    par = x;
            edges.push_back(pii(par, i));
        }

        cout << "!" << endl;
        for (pii x : edges)
            cout << x.first << " " << x.second << endl;
        
    }
}
