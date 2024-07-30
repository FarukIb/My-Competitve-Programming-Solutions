#include <bits/stdc++.h>
#define mp make_pair

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

const ll mod = 1e17 + 3;
const ll p = 53;

ll pexp[(int)2e6];
void precalc() {
    pexp[0] = 1;
    for (int i = 1; i <= 1e6; i++)
        pexp[i] = (pexp[i - 1] * p) % mod;
}

vector<vector<int> > graph;
vector<ll> hashes1;
vector<ll> hashes2;

map<ll, ll> hash1;
map<ll, ll> hash2;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    precalc();

    int n, m;
    cin >> n >> m;
    graph.resize(n + 1, vector<int>());
    hashes1.resize(n + 1, 0);
    hashes2.resize(n + 1, 0);
    for (int i = 1; i <= n; i++)
        hashes2[i] += pexp[i];
    for (int i = 0; i < m; i++) {
        int f, t;
        cin >> f >> t;
        graph[f].push_back(t);
        graph[t].push_back(f);

        hashes1[f] += pexp[t];
        hashes1[f] %= mod;
        hashes1[t] += pexp[f];
        hashes1[t] %= mod;

        hashes2[f] += pexp[t];
        hashes2[f] %= mod;
        hashes2[t] += pexp[f];
        hashes2[t] %= mod;
    }

    sort(hashes1.begin(), hashes1.end());
    sort(hashes2.begin(), hashes2.end());
    ll out = 0, curr = 1;
    for (int i = 2; i <= n; i++) {
        if (hashes1[i] != hashes1[i - 1])
            out += curr * (curr - 1) / 2, curr = 0;
        curr++;
    }
    out += curr * (curr - 1) / 2, curr = 1;

    for (int i = 2; i <= n; i++) {
        if (hashes2[i] != hashes2[i - 1])
            out += curr * (curr - 1) / 2, curr = 0;
        curr++;
    }
    out += curr * (curr - 1) / 2, curr = 0;

    cout << out << "\n";
}