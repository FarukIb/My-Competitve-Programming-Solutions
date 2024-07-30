#include <bits/stdc++.h>
#define pii pair<ll, ll>
#define ll long long
#define ld long double

using namespace std;

struct point {
    ll x, y;
    
    point() { x= 0, y = 0;}
    point (int X, int Y) { x = X, y = Y; }

    bool operator<(const point& b) const {
        if (x < b.x)
            return true;
        return y > b.y;
    }
};

ll dist(point a, point b) { return abs(a.x - b.x) + abs(a.y - b.y); }

map<ll, vector<point> > lvls;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    ll n;
    lvls[0].push_back(point(0, 0));

    cin >> n;
    for (int i = 0; i < n; i++) {
        point x;
        cin >> x.x >> x.y;

        lvls[max(x.x, x.y)].push_back(x);
    }

    vector<pair<point, point> > reps;
    for (pair<int, vector<point> > pr : lvls) {
        vector<point> clone = pr.second;
        sort(clone.begin(), clone.end());

        reps.push_back(pair<point, point>(clone[0], clone[clone.size() - 1]));
    }

    vector<pii> dp(reps.size());
    dp[0] = pii(0, 0);
    for (int i = 1; i< reps.size(); i++) {
        dp[i].first = min(dp[i - 1].first + dist(reps[i].second, reps[i - 1].first) + dist(reps[i].first, reps[i].second),
                            dp[i - 1].second + dist(reps[i].second, reps[i - 1].second) + dist(reps[i].first, reps[i].second) );
        
        dp[i].second = min(dp[i - 1].first + dist(reps[i].first, reps[i - 1].first) + dist(reps[i].first, reps[i].second),
                            dp[i - 1].second + dist(reps[i].first, reps[i - 1].second) + dist(reps[i].first, reps[i].second) );
    }

    cout << min(dp[reps.size() - 1].first, dp[reps.size() - 1].second) << "\n";
}
