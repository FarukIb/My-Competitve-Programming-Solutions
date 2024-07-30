#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <cmath>
#include <queue>
#include <stack>

using namespace std;
typedef long long ll;

vector <vector <ll>> adl;
vector <bool> isv;
vector <ll> kpnt,put;
vector <ll> par;
vector <bool> imarod;

void bfs(ll id) {
    ll tp = id;
    queue <ll> q;
    q.push(id);
    ll idx;
    isv[id] = true;
    while (q.empty() != true) {
        idx = q.front();
        q.pop();
        for (int a : adl[idx]) {
            if (!isv[a]) {
                isv[a] = true;
                par[a] = idx;
                q.push(a);
            }
        }
    }
}

int main(){
    ll n, m, a, b;
    cin >> n >> m;
    bool nmog = true;

    adl.assign(n + 1, vector<ll>());
    isv.assign(n + 1, false);
    kpnt.resize(0);
    put.resize(0);
    par.assign(n + 1, 0);
    imarod.assign(n + 1, false);
    par[1] = 0;
    imarod[1] = true;
    for (ll i = 0; i < m; i++) {
        cin >> a >> b;
        adl[a].push_back(b);
        adl[b].push_back(a);
    }
    bfs(1);
    nmog = isv[n];
    if (nmog == false)cout << "IMPOSSIBLE" << endl;
    else {
        ll l=n;
        while (l!= 0) {
            put.push_back(l);
            l = par[l];
        }
        cout << put.size() << endl;
        for (ll i = put.size() - 1; i >= 0; i--)cout << put[i] << " ";
    }
    return 0;
}