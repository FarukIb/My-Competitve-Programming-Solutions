#include <bits/stdc++.h>
#define mp make_pair
#define all(a) a.begin(), a.end()

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

const ll INF = 1e18;

struct range_max_query {
    vector<ll> tree;
    vector<ll> lazy;
    int n;

    range_max_query(vector<ll> arr) {
        n = arr.size();
        tree.resize(n*4);
        lazy.resize(n*4);
        build(0, n - 1, 1, arr);
    }

    void build(int l, int r, int idx, vector<ll> &arr) {
        if (l == r)
        {
            tree[idx] = arr[l];
            return;
        }
        int mid = (l + r) / 2;
        build(l, mid, idx * 2, arr);
        build(mid + 1, r , idx * 2 + 1, arr);
        tree[idx] = max(tree[idx * 2], tree[idx * 2 + 1]);
    }

    void push(int idx, int l, int r) {
        if (lazy[idx] == 0)
            return;
        tree[idx] += lazy[idx];
        if (l != r)
            lazy[idx * 2] += lazy[idx], lazy[idx * 2 + 1] += lazy[idx];
        lazy[idx] = 0;
    }

    void update(int l, int r, int L, int R, int idx, ll val) {
        push(idx, l , r);
        if (l > R or r < L)
            return;
        if (l >= L and r <= R) {
            lazy[idx] += val;
            push(idx, l, r);
            return;
        }
        int mid = (l + r) / 2;
        update(l, mid, L, R, idx*2, val);
        update(mid + 1, r, L, R, idx*2+1, val);
        tree[idx] = max(tree[idx * 2], tree[idx * 2 + 1]);
    }

    void update(int l, int r, ll val) {update(0, n - 1, l, r, 1, val);}

    ll query(int l, int r, int L, int R, int idx) {
        push(idx, l , r);
        if (l > R or r < L)
            return -INF;
        if (l >= L and r <= R)
            return tree[idx];
        int mid = (l + r) / 2;
        ll ans = max(query(l, mid, L, R ,idx * 2), query(mid + 1, r, L, R, idx * 2 + 1));
        tree[idx] = max(tree[idx* 2], tree[idx * 2 + 1]);
        return ans;
    }

    ll query(int l, int r) {
        if (l > r)
            return -INF;
        return query(0, n - 1, l, r, 1);
    }
};

struct poopseg {
    vector<ll> tree;
    int n;

    void update(int l, int r, ll val) {
        for (l += n, r += n + 1; l < r; l /= 2, r /= 2) {
            if (l & 1)
                tree[l++] += val;
            if (r & 1)
                tree[--r] += val;
        }
    }

    ll query(int idx) {
        ll ans = 0;
        for (idx += n; idx > 0; idx /= 2)
            ans += tree[idx];
        return ans;
    }

    poopseg(vector<ll> arr) {
        n = arr.size();
        tree.resize(n*2);
        for (int i = 0; i < n; i++)
            tree[i+n] = arr[i];
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int n, p;
    cin >> n >> p;
    vector<ll> arr(n);
    for (int i = 0; i < n; i++)
        cin >> arr[i];
    sort(all(arr));
    poopseg valseg(arr);
    for (int i = 0; i < n; i++)
        arr[i] += n - i - 1;
    range_max_query qseg(arr);

    int ans = 0;
    while (p--) {
        char t;
        cin >> t;
        if (t == 'B') {
            ll thresh, inc;
            cin >> thresh >> inc;
            int l = 0, r = n, ans = -1;
            while (l < r) {
                int mid = (l + r) / 2;
                if (valseg.query(mid) >= thresh)
                    ans = mid, r = mid;
                else
                    l = mid + 1;
            }
            if (ans != -1) {
                valseg.update(ans, n - 1, inc);
                qseg.update(ans, n - 1, inc);
            }
        } else if (t == 'K') {
            ll thresh, inc;
            cin >> thresh >> inc;
            int l = 0, r = n, ans = -1;
            while (l < r) {
                int mid = (l + r) / 2;
                if (valseg.query(mid) <= thresh)
                    l = mid + 1, ans = mid;
                else
                    r = mid;

            }
            if (ans != -1) {
                valseg.update(0, ans, -inc);
                qseg.update(0, ans, -inc);
            }
        } else {
            while (ans < n) {
                int mid = ans;
                ll lans = qseg.query(0, mid - 1) - 1, rans = qseg.query(mid + 1, n - 1);
                if (max(lans, rans) <= valseg.query(mid) + n - 1)
                    break;
                else
                    ans++;
            }
            cout << n - ans << "\n";
        }
    }
}