#include <bits/stdc++.h>
#define mp make_pair

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

bool is_edge(int f, int t, vector<vector<int> > &graph) {
    for (int i : graph[f])
        if (i == t)
            return true;
    return false;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    random_device rd;
    mt19937_64 rand(rd());
    int n, m;
    cin >> n >> m;
    vector<vector<int> > graph(n + 1);

    vector<int> edge_first;
    vector<int> guys;
    for (int i = 1; i <= n; i++)
    {
        guys.push_back(i);
        edge_first.push_back(i - 1);
    }
    for (int i = 0; i < m; i++) {
        int f, t;
        cin >> f >> t;
        graph[f].push_back(t);
        graph[t].push_back(f);
    }

    bool ok = false;
    for (int ite = 0; ite < 100; ite++) {
        shuffle(edge_first.begin(), edge_first.end(), rand);
        shuffle(guys.begin(), guys.end(), rand);
        
        bool curr = true;
        for (int i = 0; i < m; i++)
        {
            int n1 = edge_first[i], n2 = (edge_first[i] + 1) % n;
            if (is_edge(guys[n1], guys[n2], graph))
                curr = false;
        }
        if (curr)
        {
            ok = true;
            break;
        }
    }

    if (!ok)    
        cout << "-1\n";
    else {
        for (int i = 0; i < m; i++)
        {
            int n1 = edge_first[i], n2 = (edge_first[i] + 1) % n;
            cout << guys[n1] << " " << guys[n2] << "\n";
        }
    }
}