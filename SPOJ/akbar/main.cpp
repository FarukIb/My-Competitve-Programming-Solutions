#include <bits/stdc++.h>
#define mp make_pair

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int t;
    cin >> t;
    while (t--) {
        int n, r, m;
        cin >> n >> r >> m;
        vector<vector<int> > graph(n + 1);
        for (int i = 0; i < r; i++) {
            int f, t;
            cin >> f >> t;
            graph[f].push_back(t);
            graph[t].push_back(f);
        }

        vector<int> sold(n + 1, 0);
        vector<pii> soldier_list(m + 1);
        for (int i = 1; i <= m; i++)
            cin >> soldier_list[i].first >> soldier_list[i].second;
        bool overlap = false;
        for (int i = 1; i <= m; i++) {
            queue<pii> q;
            q.push(mp(soldier_list[i].first, 0));
            if (sold[soldier_list[i].first] != 0)
                overlap = true;
            sold[soldier_list[i].first] = i;
            while (!q.empty()) {
                pii curr = q.front(); q.pop();
                if (curr.second == soldier_list[i].second)
                    continue;
                for (int guy : graph[curr.first]) {
                    if (sold[guy] != 0 && sold[guy] != i)
                    {
                        overlap = true;
                        break;
                    }
                    if (sold[guy] == i)
                        continue;
                    q.push(mp(guy, curr.second + 1));
                    sold[guy] = i;
                }
                if (overlap)
                    break;  
            }
            if (overlap)
                break;
        }

        bool all_safe = true;
        for (int i = 1; i <= n; i++)
            if (sold[i] == 0)
                all_safe = false;
        if (all_safe && !overlap)
            cout << "Yes\n";
        else
            cout << "No\n";
    }
}