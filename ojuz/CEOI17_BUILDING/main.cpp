#include <bits/stdc++.h>
#define mp make_pair
#define all(a) a.begin(), a.end()

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

struct line {
    ll m, b;
    double x;
    bool is_searching;

    bool operator<(const line& b) const {
        if (is_searching || b.is_searching)
            return x < b.x;
        return m > b.m;
    }
};

typedef set<line>::iterator lineit;

set<line> hull;

bool has_prev(lineit a) {
    return a != hull.begin();
}

bool has_next(lineit b) {
    return next(b) != hull.end();
}

double intersection(lineit a, lineit b) {
    return ((double)a->b - (double)b->b) / ((double)b->m - (double)a->m);
}

void upd_x(lineit a) {
    if (has_prev(a)) {
        double point = intersection(a, prev(a));
        line copy = *a;
        copy.x = point;
        hull.erase(a);
        hull.insert(copy);
    }
}

bool bad(lineit a) {
    if (has_next(a) && next(a)->b <= a->b)
        return true;
    return (has_prev(a) && has_next(a) && intersection(prev(a), next(a)) <= intersection(prev(a), a));
}

void add_line(ll m, ll b) {
    auto it = hull.lower_bound({m, b, 0, 0});
    if (it != hull.end() && it->m == m) {
        if (it->b <= b)
            return;
        hull.erase(it);
    }
    it = hull.insert({m, b, 0, 0}).first;
    if (bad(it))
        hull.erase(it);
    else {
        while (has_prev(it) && bad(prev(it))) hull.erase(prev(it));
        while (has_next(it) && bad(next(it))) hull.erase(next(it));

        if (has_next(it)) upd_x(next(it));
        upd_x(it);
    }
}

ll query(ll val) {
    lineit l = prev(hull.upper_bound({0, 0, (double)val, 1}));
    return l->m * val + l->b;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int n;
    cin >> n;
    vector<ll> h(n);
    vector<ll> c(n);
    for (int i = 0; i<n; i++)
        cin >> h[i];
    for (int i = 0; i < n; i++)
        cin >> c[i];
    
    vector<ll> dp(n);
    dp[0] = -c[0];
    vector<ll> brute_dp(n, 1e18); brute_dp[0] = -c[0];
    for (int i = 1; i < n; i++) {
        /*for (int j = 0; j < i; j++)
            brute_dp[i] = min(brute_dp[i], brute_dp[j] + (h[i] - h[j]) * (h[i] - h[j]) - c[i]);*/
        add_line(-2*h[i - 1], h[i - 1]*h[i - 1] + dp[i - 1]);
        dp[i] = -c[i] + h[i] * h[i] + query(h[i]);
    }

    cout << accumulate(all(c), 0LL) + dp[n - 1] << "\n";
}