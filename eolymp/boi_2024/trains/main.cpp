#include <bits/stdc++.h>
#define all(a) a.begin(), a.end()

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

const ll mod = 1e9 + 7;

struct Event {
    int pidx, strt;
    bool add;
    Event() {}
    Event(int pidx, int strt, bool add) : pidx(pidx), add(add), strt(strt) {

    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int n;
    cin >> n;
    vector<int> d(n), x(n);
    vector<vector<int> > act(n);
    vector<int> idx(n);
    vector<pii> pairs;
    for (int i = 0; i < n; i++)
    {
        cin >> d[i] >> x[i];
        if (d[i] == 0)
            continue;
        pairs.push_back(pii(i % d[i], d[i]));
    }
    sort(all(pairs));
    pairs.erase(unique(all(pairs)), pairs.end());
    for (int i = 0; i < n; i++)
        if (d[i] != 0)
            idx[i] = lower_bound(all(pairs), pii(i % d[i], d[i])) - pairs.begin();
    for (int i = 0; i < pairs.size(); i++)
        act[pairs[i].first].push_back(i);

    vector<vector<Event> > Events(n); // first is pair_idx, second is 
    for (int i = 0; i < n; i++) {
        if (d[i] == 0)
            continue;
        Events[i].push_back(Event(idx[i], i, true));
        ll endd = (ll)i + (ll)d[i] * (ll)x[i];
        if (endd < n)
            Events[endd].push_back(Event(idx[i], i, false));
    }

    vector<ll> dp(n);
    dp[0] = 1;
    vector<ll> pair_sum(pairs.size());
    
    ll out = 0;
    for (int i = 0; i < n; i++) {
        for (int j : act[i])
        {
            dp[i] = (dp[i] + pair_sum[j]) % mod;
            if (i + pairs[j].second < n)
                act[i + pairs[j].second].push_back(j);
        }
        act[i].clear();
        for (Event e : Events[i])
        {
            if (e.add)
                pair_sum[e.pidx] = (pair_sum[e.pidx] + dp[e.strt]) % mod;
            else
                pair_sum[e.pidx] = (pair_sum[e.pidx] - dp[e.strt] + mod) % mod;
        }
        out = (dp[i] + out) % mod;
    }

    cout << out << "\n";
}