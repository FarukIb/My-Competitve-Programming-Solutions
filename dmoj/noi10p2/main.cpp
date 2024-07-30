#include <bits/stdc++.h>
#define all(a) a.begin(), a.end()

using namespace std;

typedef long long ll;
typedef pair<ll, ll> pii;

const ll INF = 1e9;

int min_val, max_val;

struct sum_seg {
    vector<ll> tree;
    ll n;

    sum_seg() {}
    sum_seg(ll n) : n(n) {
        tree = vector<ll> (2 * n);
    }

    ll query(ll l, ll r) {
        if (l > r)
            return 0;
        ll ans = 0;
        for (l += n, r += n + 1; l < r; l /= 2, r /= 2) {
            if (l & 1)
                ans += tree[l++];
            if (r & 1)
                ans += tree[--r];
        }
        return ans;
    }

    void upd(ll idx, ll val) {
        for (idx += n; idx > 0; idx /= 2)
            tree[idx] += val;
    }
};

struct seggy {
    vector<pii> tree;
    ll n;

    seggy() {}
    seggy(vector<ll> arr) {
        n = arr.size();
        tree = vector<pii> (2 * n);
        for (ll i = n; i < 2 * n; i++)
            tree[i] = pii(arr[i - n], i - n);
        for (ll i = n - 1; i > 0; i--)
            tree[i] = max(tree[i * 2], tree[i * 2 + 1]);
    }

    pii query(ll l, ll r) {
        if (l > r)
            return pii(-INF, 0);
        pii ans(-INF, 0);
        for (l += n, r += n + 1; l < r; l /= 2, r /= 2) {
            if (l & 1)
                ans = max(ans, tree[l++]);
            if (r & 1)
                ans = max(ans, tree[--r]);
        }
        return ans;
    }

    void upd(ll idx, ll val) {
        idx += n;
        tree[idx].first = val;
        for (idx /= 2; idx > 0; idx /= 2)
            tree[idx] = max(tree[idx * 2], tree[idx * 2 + 1]);
    }
};

ll n, k, x, y;
vector<ll> arr;

vector<ll> comp_arr;
map<ll, ll> trans;
void compress() {
    vector<ll> tmp = arr;
    sort(all(tmp));
    tmp.erase(unique(all(tmp)), tmp.end());
    for (int i = 0; i < tmp.size(); i++)
        trans[tmp[i]] = i;
    trans[INF] = tmp.size();
    for (int i = 0; i < arr.size(); i++)
        comp_arr.push_back(trans[arr[i]]);
    comp_arr.push_back(INF);
}

sum_seg seg2;
ll count_bigger(ll val) {
    ll out = 0;
    vector<bool> there(n + 1);
    for (ll i = 1; i <= n; i++) {
        ll l = i + x - 1, r = i + y - 1;
        if (i == 1)
        {
            for (ll j = l; j <= min(n, r); j++)
                seg2.upd(comp_arr[j], 1), there[j] = true;
        } else {
            if (l - 1 <= n) {
                seg2.upd(comp_arr[l - 1], -1);
                there[l - 1] = false;
            }
            
            if (r <= n)
                seg2.upd(comp_arr[r], 1), there[r] = true;
        }

        ll needed = val + arr[i - 1];
        out += seg2.query(trans.lower_bound(needed)->second, comp_arr.size() - 1);
        if (out > k) {
            for (ll i = 1; i <= n; i++)
                if (there[i])
                    seg2.upd(comp_arr[i], -1);
            return k + 1;
        }
    }

    for (ll i = 1; i <= n; i++)
        if (there[i])
            seg2.upd(comp_arr[i], -1);

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
    compress();

    seggy seg(arr);
    seg2 = sum_seg(comp_arr.size());

    min_val = *min_element(all(arr));
    max_val = *max_element(all(arr));

    ll l = min_val, r = max_val + 1, ans = min_val; // sto veci mid to manji count bigger
    while (l < r) {
        ll mid = (l + r + 2 * INF) / 2 - INF;
        if (count_bigger(mid) > k)
            l = mid+ 1, ans = mid;
        else // ovdje je <= k
            r = mid;
    }

    ll out = 0;
    ll done = 0;
    for (ll i = 1; i <= n; i++) {
        ll l = i + x - 1, r = min(n, i + y - 1);
        ll minimum = ans + arr[i - 1];
        vector<ll> removed;
        while (seg.query(l, r).first > minimum) {
            done++;
            pii guy = seg.query(l, r);
            removed.push_back(guy.second);
            out += seg.query(l, r).first - arr[i - 1];
            seg.upd(guy.second, -INF);
        }
        for (ll rem : removed)
            seg.upd(rem, arr[rem]);
    }

    out += (ll)(k - done) * (ans);
    cout << out << "\n";
}