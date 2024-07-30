#include <iostream>
#include <set>
#include <algorithm>
#include <vector>
#define mp make_pair
#define all(a) a.begin(), a.end()

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

const ll mod = 1e9 + 7;
const ll p = 31;
const ll maxn = 1e6 + 1;

ll bin_expo(ll base, ll expo) {
    if (expo == 0)
        return 1;
    ll half = bin_expo(base, expo / 2);
    half *= half, half %= mod;
    if (expo % 2)
        half *= base, half %= mod;
    return half;
}

vector<ll> powp(maxn);
vector<ll> invpowp(maxn);
string s;
int n;

vector<ll> hashh;
vector<ll> revhash;

void init() {
    n = s.size();
    powp[0] = 1;
    invpowp[0] = 1;
    for (int i = 1; i < maxn; i++)
        powp[i] = powp[i - 1] * p % mod, invpowp[i] = bin_expo(powp[i], mod - 2);
    hashh.resize(n + 1);
    for (int i = 0; i < n; i++) {
        hashh[i] = (ll)(s[i] - 'a') * powp[i] % mod;
        if (i != 0)
            hashh[i] += hashh[i - 1], hashh[i] %= mod;
    }

    revhash.resize(n + 1);
    for (int i = n - 1; i >= 0; i--) {
        revhash[i] = (ll)(s[i] - 'a') * powp[n - 1 - i] % mod;
        if (i != n - 1)
            revhash[i] += revhash[i + 1], revhash[i] %= mod;
    }
}

ll get_hash(int l, int r) {
    ll h = hashh[r];
    if (l != 0)
        h -= hashh[l - 1];
    h %= mod;
    if (h < 0)
        h += mod;

    h *= invpowp[l], h %= mod;
    return h;
}

ll get_rev_hash(int l, int r) {
    ll h = revhash[l];
    if (r != n - 1)
        h -= revhash[r + 1];
    h %= mod;
    if (h < 0)
        h += mod;
    h *= invpowp[n - r - 1], h %= mod;
    return h;
}

int distt(set<pii>::iterator it, set<pii>& ls, set<pii>& rs, bool froml) {
    auto next_r = next(rs.lower_bound({ it->first, 0 }));
    int out = next_r->first - it->first - 1;
    auto next_l = ls.lower_bound({ it->first + 1, 0 });
    if (next_l != ls.end()) {
        if (!froml)
            out = min(out, (next_l->first - it->first) / 2);
        else
            out = min(out, next_l->first - it->first - 1);
    }
    return max(0, out);
}

int update(set<pii>::iterator it, set<pii>& ls, set<pii>& rs, bool froml) {
    int d = distt(it, ls, rs, froml);
    int idx = it->first;
    if (froml) {
        ls.erase(it);
        ls.insert({ idx, d });
    }
    else {
        rs.erase(it);
        rs.insert({ idx, d });
    }
    return d;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    cin >> s;
    init();

    vector<int> max_normal(n);
    vector<int> max_rev(n);
    // compute max_normal
    vector<pii> rs;
    for (int i = 0; i < n; i++) {
        int l = 0, r = n - i, ans = -1;
        while (l < r) {
            int mid = (l + r) / 2;
            if (get_hash(0, mid) == get_hash(i, i + mid))
                ans = mid, l = mid + 1;
            else
                r = mid;
        }
        max_normal[i] = ans;
        if (ans != -1)
            rs.push_back({ ans, i });
    }

    vector<pii> ls;
    // compute max_rev
    int val = 0;
    for (int i = 0; i < n; i++) {
        // we assume we are the end
        int l = 0, r = i + 1, ans = -1;
        while (l < r) {
            int mid = (l + r) / 2;
            ll myhash = get_rev_hash(i - mid, i);
            ll prefhash = get_hash(0, mid);
            if (myhash == prefhash)
                ans = mid, l = mid + 1;
            else
                r = mid;
        }
        max_rev[i] = ans;
        if (ans != -1)
            ls.push_back({ ans, i });
    }

    sort(all(ls), greater<pii>()); int pnt1 = 0;
    sort(all(rs), greater<pii>()); int pnt2 = 0;

    multiset<int> dists;
    set<pii> r_pnts, l_pnts;
    r_pnts.insert({ n, 0 });
    vector<int> out;
    for (int d = n - 1; d >= 0; d--) {
        vector<int> ladded;
        while (pnt1 < ls.size() and ls[pnt1].first >= d)
        {
            ladded.push_back(ls[pnt1].second);
            pii p = mp(ls[pnt1].second, 0);
            l_pnts.insert(p);
            pnt1++;
        }
        vector<int> to_addr;
        while (pnt2 < rs.size() and rs[pnt2].first >= d)
        {
            to_addr.push_back(rs[pnt2].second);
            r_pnts.insert({ rs[pnt2++].second, 0 });
        }

        for (int a : to_addr) {
            auto me = r_pnts.lower_bound({ a, 0 });
            int dd = *dists.insert(update(me, l_pnts, r_pnts, false));
            me = r_pnts.find({a, dd});
            if (me != r_pnts.begin()) {
                auto prevv = prev(me);
                if (max_normal[prevv->first] != d) {
                    dists.erase(dists.find(prevv->second));
                    dists.insert(update(prevv, l_pnts, r_pnts, false));
                }
            }
            auto inl = l_pnts.lower_bound({ a, 0 });
            if (inl != l_pnts.begin()) {
                auto prevv = prev(inl);
                if (max_rev[prevv->first] != d) {
                    dists.erase(dists.find(me->second));
                    dists.insert(update(me, l_pnts, r_pnts, true));
                }
            }
        }
        for (int a : ladded) {
            auto me = l_pnts.lower_bound({ a, 0 });
            int dd = *dists.insert(update(me, l_pnts, r_pnts, true));
            me = l_pnts.find({a, dd});
            if (me != l_pnts.begin()) {
                auto prevv = prev(me);
                if (max_rev[prevv->first] != d) {
                    dists.erase(dists.find(prevv->second));
                    dists.insert(update(prevv, l_pnts, r_pnts, true));
                }
            }
            auto inr = r_pnts.lower_bound({ a, 0 });
            if (inr != r_pnts.begin()) {
                auto prevv = prev(inr);
                if (max_normal[prevv->first] != d) {
                    dists.erase(dists.find(prevv->second));
                    dists.insert(update(prevv, l_pnts, r_pnts, false));
                }
            }
        }

        int d_to_cover = 1e9;
        if (!l_pnts.empty() and l_pnts.rend()->first != n - 1) {
            if (l_pnts.size() != 1)
                d_to_cover = n - prev(l_pnts.rend())->first - 1;
            else if (l_pnts.lower_bound({ prev(r_pnts.end())->first + 1, 0 }) != l_pnts.begin())
                d_to_cover = 0;
        }
        else {
            d_to_cover = 0;
        }
        dists.insert(d_to_cover);
        if (*prev(dists.end()) <= d)
            out.push_back(d + 1);
        dists.erase(d_to_cover);
    }

    reverse(all(out));
    for (int a : out)
        cout << a << " ";
    cout << "\n";
}