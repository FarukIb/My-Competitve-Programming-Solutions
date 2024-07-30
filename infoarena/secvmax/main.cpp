#include <bits/stdc++.h>
#define pii pair<int, int>
#define ll long long
#define ld long double

using namespace std;

int ufds[200000];
int child[200000];

int maxi = 1;

int find(int x) {
    if (ufds[x] == x)
        return x;
    return ufds[x] = find(ufds[x]);
}

void merge(int a, int b) {
    if (find(a) != find(b)) {
        child[find(b)] += child[find(a)];
        ufds[find(a)] = find(b);

        maxi = max(maxi, child[find(b)]);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    freopen("secvmax.in", "r", stdin);
    freopen("secvmax.out", "w", stdout);

    int n, q;
    cin >> n >> q;

    vector<int> arr(n);

    vector<int> all;
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
        ufds[i] = i;
        child[i] = 1;
        all.push_back(arr[i]);
    }

    vector<pii> queries(q);
    for (int i = 0; i < q; i++)
    {
        cin >> queries[i].first;
        queries[i].second = i;
        all.push_back(queries[i].first);
    }
    sort(all.begin(), all.end());
    int br = 1, maxel, mini = 1e9;
    map<int, int> comp;
    comp[all[0]] = 0;
    for (int i = 1; i < all.size(); i++) {
        if (all[i] != all[i - 1])
            comp[all[i]] = br, br++;
    }
    auto last = comp.end(); last--;
    maxel = last->second;

    vector<vector<int> > idxs(maxel + 1, vector<int>());
    for (int i = 0; i < n; i++)
    {
        arr[i] = comp[arr[i]];
        idxs[arr[i]].push_back(i);
        mini = min(mini, arr[i]);
    }
    vector<int> val(maxel + 1, 1);
    for (int j = 0; j < q; j++)
        queries[j].first = comp[queries[j].first];
    
    for (int i = 0; i <= maxel; i++) {
        for (int s : idxs[i]) {
            if (s != 0 && arr[s] >= arr[s - 1])
                merge(s, s - 1);
            if (s != n -1 && arr[s] >= arr[s + 1])
                merge(s, s + 1);
        }
        val[i] = maxi;
    }

    vector<int> out(q);
    for (int i = 0; i < q; i++)
    {
        out[queries[i].second] = val[queries[i].first];
        if (queries[i].first < mini)
            out[queries[i].second] = 0;
    }
    for (int i = 0; i < q; i++)
        cout << out[i] << "\n";
}
