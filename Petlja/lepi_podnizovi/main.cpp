#include <bits/stdc++.h>
#define pii pair<ll, ll>
#define ll long long
#define ld long double

using namespace std;

pii mmax(pii a, pii b) {
    if (a.first > b.first)
        return a;
    else if (a.first == b.first && a.second < b.second)
        return a;
    return b;
}

struct seggy {
    vector<pii> tree;
    ll n;
    seggy (vector<ll> arr) {
        n = arr.size();
        tree.resize(n * 2, {0, 0});
        for (ll i = 0; i < n; i++)
            tree[i + n] = {arr[i], i};
        for (ll i = n - 1; i > 0; i--)
            tree[i] = max(tree[i * 2], tree[i * 2 + 1]);
    }

    pii query(ll l, ll r) {
        pii out(0, 0);
        for (l += n, r += n; l < r; l /= 2, r /= 2)
        {
            if (l & 1)
                out = max(out, tree[l++]);
            if (r & 1)
                out = max(out, tree[--r]);
        }
        return out;
    }
};

bool cmp(pii a, pii b) {
    if (a.first < b.first)
        return true;
    else if (a.first == b.first && a.second > b.second)
        return true;
    return false;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    ll n;
    cin >> n;
    vector<ll> arr(n);

    vector<pii> order;
    for (ll i = 0; i < n; i++)
    {
        cin >> arr[i];
        order.push_back({arr[i], i});
    }
    sort(order.begin(), order.end());
    seggy seg(arr);

    set<ll> lower;
    lower.insert(n);

    ll out = 0;
    for (ll i = 0; i < n; i++) {
        ll where = (*lower.lower_bound(order[i].second));
        ll end = seg.query(order[i].second, where).second;
        lower.insert(order[i].second);
        out = max(out, end - order[i].second + 1);
    }

    if (out == 1)
        out = 0;
    cout << out << "\n";
}
