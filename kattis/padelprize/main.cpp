#include <bits/stdc++.h>
#define mp make_pair
#define all(a) a.begin(), a.end()

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

int n, m;
vector<int> x;
vector<int> y;

vector<vector<int> > idxs;
vector<int> out;

set<pii> lengths;
vector<bool> visited;
map<int, int> eachlen;
void recur(int day) {
    visited[day] = true;
    out[-prev(lengths.end())->second]++;
    for (int guy : {x[day], y[day]}) {
        if (idxs[guy][0] == day)
            continue;
        int pre = *prev(lower_bound(all(idxs[guy]), day));
        if (y[pre] == guy)
            continue;

        lengths.erase({eachlen[guy],-guy});
        eachlen[guy] += (day-pre);
        lengths.insert({eachlen[guy], -guy});
        recur(pre);
        lengths.erase({eachlen[guy], -guy});
        eachlen[guy] -= (day-pre);
        lengths.insert({eachlen[guy], -guy});
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    cin >> n >> m;
    x.resize(m);
    y.resize(m);
    out.resize(n);
    idxs.resize(n);
    visited.resize(m);

    for (int i = 0; i < m; i++) {
        cin >> x[i] >> y[i];
        idxs[x[i]].push_back(i);
        idxs[y[i]].push_back(i);
    }

    for (int i = m - 1; i >= 0; i--) {
        if (visited[i])
            continue;
        eachlen[x[i]] = (m - i);
        lengths.insert({m-i, -x[i]});
        recur(i);
        eachlen.clear();
        lengths.clear();
    }

    for (int a : out)
        cout <<a << " ";
    cout << "\n";
}