#include <bits/stdc++.h>
#define mp make_pair
#define all(a) a.begin(), a.end()

using namespace std;

typedef long long ll;
typedef pair<ll, ll> pii;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    ll n;
    cin >> n;
    vector<ll> arr(n);
    for (ll i = 0; i < n; i++)
        cin >> arr[i];

    vector<ll> cost(n + 1, 2e9);
    vector<ll> mincost(n+2, 2e9);
    for (ll i = 1; i <= n; i++)
        cin >> cost[i];
    for (int i = n; i > 0; i--) 
        mincost[i] = min(cost[i], mincost[i + 1]);
    
    vector<vector<ll> > graph(n + 1);
    for (ll i = 1; i< n; i++) {
        ll f,t;
        cin >>f >> t;
        graph[f].push_back(t);
        graph[t].push_back(f);
    }

    vector<vector<ll> > chains;
    vector<ll> curr(1, arr[0]);
    for (ll i = 1; i < n; i++) {
        if (arr[i] - arr[i - 1] == 1 || arr[i] == 0)
            curr.push_back(arr[i]);
        else {
            chains.push_back(curr);
            curr = vector<ll>(1, arr[i]);
        }
    }
    chains.push_back(curr);

    ll out = 0;
    for (vector<ll> c : chains) {
        vector<ll> compressed;
        for (int i = 1; i < c.size(); i++)
            if (c[i] == 0)
                compressed.push_back(i == 0 ? 0 : c[i - 1]);
        if (compressed.empty()) 
            compressed.push_back(c[c.size() - 1]);
        else {
            if (c[c.size() - 1] > compressed[compressed.size() - 1])
                compressed.push_back(c[c.size() - 1]);
            else
                compressed.push_back(compressed[compressed.size() - 1]);
        }
        
        ll in_a_row = 0;
        for (int i = 0; i < compressed.size(); i++) {
            if (i == 0 || compressed[i] == compressed[i - 1])
                in_a_row++;
            else
            {
                int last = i == 0 ? 0 : compressed[i - 1];
                out += min(cost[last + 1], in_a_row*mincost[last + 1]);
                in_a_row = 1;
            }
        }
        int i = compressed.size();
        int last = i == 0 ? 0 : compressed[i - 1];
        out += min(cost[last + 1], in_a_row*mincost[last + 1]);
    }
    cout << out << "\n";
}
