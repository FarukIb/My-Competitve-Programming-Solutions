#include <bits/stdc++.h>
#define mp make_pair

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

const int maxn = 1e5 + 10;
const ll mod = 1e9 + 7;

ll expo(ll base, ll stepen) {
    if (stepen == 0)
        return 1;
    ll half = expo(base, stepen / 2); half *= half, half %= mod;
    if (stepen % 2)
        half *= base, half %= mod;
    return half;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    vector<vector<int> > facts(maxn);
    for (int i = 1; i < maxn; i++)
        for (int j = i; j < maxn; j += i)
            facts[j].push_back(i);

    int n;
    cin >> n;
    vector<int> arr(n);
    for (int i = 0; i < n; i++)
        cin >> arr[i];
    sort(arr.begin(), arr.end());
    ll out = 0;
    for (int i = 1; i < maxn; i++) {
        vector<int> occur(facts[i].size(), 0);
        for (int j = 0; j < facts[i].size(); j++) {
            int p = facts[i][j];
            int place = lower_bound(arr.begin(), arr.end(), p) - arr.begin();
            occur[j] = arr.size() - place;
        }

        for (int j = 0; j < facts[i].size() - 1; j++)
            occur[j] -= occur[j + 1];
        ll curr = 1;
        for (int j = 0; j < facts[i].size() - 1; j++)
            curr *= expo(j + 1, occur[j]), curr %= mod;
        int dx = facts[i].size();
        if (occur[dx - 1] == 0)
            continue;
        ll last = expo(dx, occur[dx - 1]) - expo(dx - 1, occur[dx - 1]);
        last %= mod;
        if (last < 0)
            last += mod;
        
        curr *= last, curr %= mod;
        out += curr;
        out %= mod;
    }

    cout << out << "\n";
}