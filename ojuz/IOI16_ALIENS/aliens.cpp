#include "aliens.h"
#include <bits/stdc++.h>
#define intsum(a) (a.second - a.first + 1LL) * (a.second - a.first + 1LL)
#define all(a) a.begin(), a.end()

using namespace std;

typedef long long ll;
typedef pair<ll, ll> pii;

const ll INF = 1e18;

bool cmp(pii a, pii b) {return pii(a.first, -a.second) < pii(b.first, -b.second);}

vector<pii> get_intervals(vector<int> r, vector<int> c) {
    vector<pii> all_intervals;
    for (int i = 0; i < r.size(); i++)
        all_intervals.push_back({min(r[i], c[i]), max(r[i], c[i])});
    sort(all(all_intervals), cmp);

    vector<pii> intervals;
    for (pii a : all_intervals) {
        if (intervals.size() == 0) {
            intervals.push_back(a);
        } else {
            pii last = *prev(intervals.end());
            if (last.second < a.second)
                intervals.push_back(a);
        }
    }
    return intervals;
}

long long take_photos(int n, int m, int k, std::vector<int> r, std::vector<int> c) {
    vector<pii> ints = get_intervals(r, c);
    ints.insert(ints.begin(), pii(-1, -1));

    auto cost = [&](int l, int j) {
        ll cos = intsum(pii(ints[l].first, ints[j].second));

        pii intersection_interval(ints[l].first, ints[l - 1].second);
        if (intersection_interval.first <= intersection_interval.second)
            cos -= intsum(intersection_interval);
        return cos;
    };

    vector<vector<ll> > dp(k + 1, vector<ll>(ints.size() + 1, INF));
    vector<vector<ll> > opt(k + 1, vector<ll> (ints.size() + 1, 0));
    for (int i = 0; i <= min(k, (int)ints.size()); i++)
        opt[i][i] = i;
    dp[0][0] = 0;
    for (int i = 1; i <= k; i++) {
        dp[i][0] = 0;
        for (int j = ints.size(); j > 0; j--) {
            for (int l = opt[i - 1][j]; l <= min(j - 1, opt[i][j + 1]); l++) {
                ll cos = dp[i - 1][l - 1] + cost(l, j);
                
                dp[i][j] = min(dp[i][j], cos);
            }
        }
    }

    return dp[k][ints.size() - 1];
}
