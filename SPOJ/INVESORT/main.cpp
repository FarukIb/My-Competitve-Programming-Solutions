#include <bits/stdc++.h>
#define mp make_pair
#define all(a) a.begin(), a.end()

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

int solve(string a, string b) {
    if (a == b)
        return 0;
    unordered_map<string, pair<int, char> > dist;
    dist[b] = {0, 'b'};
    dist[a] = {0, 'a'};
    queue<string> q; q.push(a); q.push(b);
    while (!q.empty()) {
        string cur = q.front(); q.pop(); pair<int, char> d = dist[cur];
        for (int i = 0; i < 10; i++) {
            for (int j = i + 1; j < 10; j++) {
                reverse(cur.begin() + i, cur.begin() + j + 1);
                if (!dist.count(cur)) {
                    dist[cur] = {d.first + 1, d.second};
                    q.push(cur);
                } else if (dist[cur].second != d.second) {
                    return dist[cur].first + d.first + 1;
                }
                reverse(cur.begin() + i, cur.begin() + j + 1);
            }
        }
    }
    return 0;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    string a, b;
    while (cin >> a >> b) {
        if (a == "*")
            return 0;
        cout << solve(a, b) << "\n";
    }
}