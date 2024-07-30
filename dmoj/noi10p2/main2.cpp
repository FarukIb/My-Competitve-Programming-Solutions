#include <bits/stdc++.h>
#define all(a) a.begin(), a.end()

using namespace std;

typedef long long ll;
typedef pair<ll, ll> pii;

const ll INF = 2e9;

ll k;

struct merge_sort_seg {
    vector<vector<ll> > tree;
    vector<vector<ll> > queries_val;
    vector<ll> sum;
    vector<ll> arr;
    ll n;


    merge_sort_seg() {}
    merge_sort_seg(vector<ll> arrr) {
        n = arrr.size();
        arr = arrr;
        vector<pii> b;
        for (int i = 0; i < n; i++)
            b.emplace_back(arr[i], i);
        sort(all(b));
        sum = vector<ll> (2 * n);
        tree = queries_val = vector<vector<ll> > (n * 2);
        for (auto [val, idx] : b)
            for (idx += n; idx > 0; idx /= 2)
                tree[idx].push_back(val), sum[idx] += val;
        
    }

    ll query(ll l, ll r, ll val) {
        ll out = 0;
        for (l += n, r += n + 1; l < r; l /= 2, r /= 2) {
            if (l & 1)
                queries_val[l++].push_back(val);
            if (r & 1)
                queries_val[--r].push_back(val);
        }
        return 0;
    }

    ll sum_queries(ll val, bool sum_val) {
        ll out = 0;
        for (int i = 1; i < 2 * n; i++) {
            if (queries_val[i].empty())
                continue;
            int pnt = 0;
            ll sum_so_far = 0;
            for (int j = 0; j < queries_val[i].size(); j++) {
                while (pnt < tree[i].size() and tree[i][pnt] < queries_val[i][j] + val)
                    sum_so_far += tree[i][pnt], pnt++;
                if (!sum_val)
                    out += tree[i].size() - pnt;
                else
                    out += sum[i] - sum_so_far - (tree[i].size() - pnt) * queries_val[i][j];
            }
        }
        return out;
    }
};

ll n, x, y;
vector<ll> arr;
merge_sort_seg mer_seg;
vector<pair<ll, pii> > queries;
void init_queries() {
    for (ll i = 1; i <= n; i++) {
        ll l = i + x - 1, r = min(n, i + y - 1);
        ll needed = arr[i - 1];
        queries.push_back(pair<ll, pii>(needed, pii(l, r)));
    }
    sort(all(queries));
    for (auto [vall, gran] : queries)
        mer_seg.query(gran.first, gran.second, vall);
}

ll count_bigger(ll val) {
    ll out = 0;
    
    out = mer_seg.sum_queries(val, false);
    return out;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    cin >> n >> k >> x >> y;
    arr = vector<ll>(n + 1);
    for (ll i = 1; i <= n; i++) {
        cin >> arr[i];
        arr[i] = arr[i - 1] + arr[i];
    }
    
    mer_seg = merge_sort_seg(arr);
    init_queries();

    ll l = -INF, r = INF, ans = -INF; // sto veci mid to manji count bigger
    while (l < r) {
        ll mid = (l + r + 2 * INF) / 2 - INF;
        if (count_bigger(mid) > k)
            l = mid+ 1, ans = mid;
        else // ovdje je <= k
            r = mid;
    }

    ll out = mer_seg.sum_queries(ans, true);
    ll done = mer_seg.sum_queries(ans, false);

    out += (ll)(k - done) * (ans);
    cout << out << "\n";
}