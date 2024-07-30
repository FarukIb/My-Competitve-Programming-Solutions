#include <bits/stdc++.h>
#define mp make_pair

using namespace std;

typedef long long ll;
typedef pair<ll, ll> pii;

const ll K = 20;
const ll inf = 2e9;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    ll n, q;
    cin >> n >> q;

    vector<ll> arr(n);
    vector<ll> prefsum(n + 1);
    for (ll i = 0; i < n; i++)
    {
        cin >> arr[i];
        prefsum[i + 1] = arr[i];
        prefsum[i + 1] += prefsum[i];
    }
    
    vector<vector<pii> > lift(K, vector<pii>(n, mp(inf, inf)));

    stack<pii> stck;
    stck.push(mp(inf, inf));
    for (ll i = n - 1; i >= 0; i--) {
        while (stck.top().first < arr[i]) 
            stck.pop();
        ll cost = 1e9;
        if (stck.top().first != inf)
        {
            cost = (stck.top().second - i) * arr[i];
            ll sum = prefsum[stck.top().second] - prefsum[i];
            cost -= sum;
        }
        lift[0][i] = mp(stck.top().second, cost);
        stck.push(mp(arr[i], i));
    }

    for (ll i = n - 1; i >= 0; i--) {
        for (ll j = 1; j < K; j++) {
            ll par = lift[j - 1][i].first;
            ll cost = lift[j - 1][i].second;
            if (par == inf)
                continue;
            ll parspar = lift[j - 1][par].first;
            if (parspar == inf)
                continue;
            cost += lift[j - 1][par].second;
            lift[j][i] = mp(parspar, cost);
        }
    }

    while (q--) {
        ll l, r;
        cin >> l >> r;
        l--, r--;
        ll out = 0;
        for (ll i = K - 1; i >= 0; i--) {
            if (lift[i][l].first > r)
                continue;
            out += lift[i][l].second;
            l = lift[i][l].first;
        }

        out += (r - l + 1LL) * arr[l] - (prefsum[r + 1] - prefsum[l]);
        cout << out << "\n";
    }
}
