#include <bits/stdc++.h>
#define mp make_pair
#define all(a) a.begin(), a.end()

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

const ll mod = 1e9 + 7;
const ll maxn = 4e5;

ll bin_expo(ll base, ll xp) {
    if (xp == 0)
        return 1;
    ll half = bin_expo(base, xp / 2);
    half = half * half % mod;
    if (xp % 2)
        half = half * base % mod;
    return half;
}

ll mod_inv(ll a) {
    return bin_expo(a, mod - 2);
}

ll add(ll a, ll b) {
    return (((a % mod) + (b % mod)) % mod + mod) % mod;
}

ll mult(ll a, ll b) {
    return (((a % mod) * (b % mod)) % mod + mod) % mod;
}

vector<ll> fact, invfact;
void init() {
    fact = invfact = vector<ll> (maxn, 1);
    for (int i = 1; i < maxn; i++)
        fact[i] = mult(fact[i - 1], i);
    invfact[maxn - 1] = mod_inv(fact[maxn - 1]);
    for (int i = maxn - 2; i >= 0; i--)
        invfact[i] = mod_inv(fact[i]);
}

ll bin_coef(ll n, ll k) {
    return mult(fact[n], mult(invfact[k], invfact[n - k]));
}

struct info {
    int maxi, maxi_idx;
    int mini, mini_idx;
    int cnt;

    info() {
        maxi = -1, mini = 2e9, maxi_idx = 0, mini_idx = 0, cnt = 0;
    }
    info(int idx, int val) {
        maxi = mini = val;
        mini_idx = maxi_idx = idx;
        cnt = 1;
    }
};

info merge(info a, info b) {
    info neww;
    neww.maxi = max(a.maxi, b.maxi);
    neww.mini = min(a.mini, b.mini);
    neww.cnt = a.cnt + b.cnt;
    if (neww.maxi == a.maxi)
        neww.maxi_idx = a.maxi_idx;
    else
        neww.maxi_idx = b.maxi_idx;
    if (neww.mini == a.mini)
        neww.mini_idx = a.mini_idx;
    else
        neww.mini_idx = b.mini_idx;
    return neww;
}

struct seggy {
    vector<info> seg;
    int n;

    seggy() {}
    seggy(vector<int> arr) {
        n = arr.size();
        seg = vector<info> (2 * n);
        for (int i = n; i < 2 * n; i++)
            seg[i] = info(i - n, arr[i - n]);
        for (int i = n - 1; i > 0; i--)
            seg[i] = merge(seg[i * 2], seg[i * 2 + 1]);
    }

    void set(int idx, info val) {
        for (idx += n, seg[idx] = val, idx /= 2; idx > 0; idx /= 2)
            seg[idx] = merge(seg[idx * 2], seg[idx * 2 + 1]);
    }

    info query(int l, int r) {
        info out;
        for (l += n, r += n + 1; l < r; l /= 2, r /= 2) {
            if (l & 1)
                out = merge(out, seg[l++]);
            if (r & 1)
                out = merge(out, seg[--r]);
        }
        return out;
    }
};

int n, k;
seggy seg;

ll recur(int l, int r) {
    if (r <= l)
        return 1;
    info all = seg.query(l, r);
    if (all.cnt <= 1) 
        return 1;
    // case 1, cant move so split
    
    if (all.maxi + all.mini > k) {
        if (all.maxi_idx == r)
            return recur(l, r - 1);
        if (all.maxi_idx == l)
            return recur(l + 1, r);
        return mult(recur(l, all.maxi_idx), recur(all.maxi_idx + 1, r));
    }
    // case 2
    ll num_mini = 0;
    while (1) {
        info curr = seg.query(l, r);
        if (curr.mini != all.mini)
            break;
        num_mini++;
        seg.set(curr.mini_idx, info());
    }
    ll arrangements = bin_coef(all.cnt, num_mini);
    return mult(arrangements, recur(l, r));
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    init();

    cin >> n >> k;
    vector<int> arr(n);
    for (int i = 0; i < n; i++)
        cin >> arr[i];
    seg = seggy(arr);
    cout << recur(0, n - 1) << "\n";
}