#include <bits/stdc++.h>
#define mp make_pair
#define all(a) a.begin(), a.end()

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;
typedef pair<pii, int> ppiii;

vector<pii> moves = {{-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1}};

map<pii, int> ind;
set<pii> there;
set<pii> visited;
void dfs(pii a) {
    visited.insert(a);
    for (pii b : moves){
        pii neww(a.first + b.first, a.second + b.second);
        if (!visited.count(neww) and there.count(neww))
            dfs(neww);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int n;
    int t;
    cin >> n >> t;
    for (int i = 0; i < n; i++) {
        pii a;
        cin >> a.first >> a.second;
        there.insert(a);
        ind[a] = i + 1;
    }
    dfs(*there.begin());
    if (visited.size() != n) {
        cout <<"NO\n";
        return 0;
    }

    cout << "YES\n";
    queue<pii> q;
    q.push(*there.begin());
    visited.clear();
    while (!q.empty()) {
        pii a = q.front(); q.pop();
        cout << ind[a] << "\n";
        visited.insert(a);
        for (pii b : moves) {
            pii neww(a.first + b.first, a.second + b.second);
            if (!visited.count(neww) and there.count(neww))
                q.push(neww);
        }
    }
}