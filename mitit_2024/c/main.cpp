#include <bits/stdc++.h>
#define mp make_pair
#define all(a) a.begin(), a.end()

using namespace std;

typedef long long ll;
typedef pair<ll, ll> pii;
 
struct seggy {
    vector<ll> tree;
    vector<ll> lazy;
    vector<ll> sett;
    ll n;
 
    seggy(vector<ll> arr) {
        n = arr.size();
        tree.resize(n * 4, 0);
        lazy.resize(n * 4, 0);
        sett.resize(n * 4, 0);
        build(1, 0, n - 1, arr);
    }
 
    void build(ll idx, ll l, ll r, vector<ll> &arr) {
        if (l == r)
        {
            tree[idx] = arr[l];
            return;
        }
        ll mid = (l + r) / 2;
        build(idx * 2 + 1, l, mid, arr);
        build(idx * 2 + 2, mid + 1, r, arr);
        tree[idx] = tree[idx * 2 + 1] + tree[idx * 2 + 2];
    }
 
    void push(ll idx, ll l, ll r) {
        if (sett[idx] != 0){
            tree[idx] = (r - l + 1) * sett[idx];
            if (l != r)
                sett[idx * 2 + 1] = sett[idx], sett[idx * 2 + 2] = sett[idx], 
                lazy[idx * 2 + 1] = 0, lazy[idx * 2 + 2] = 0;
            sett[idx] = 0;
        }
 
        tree[idx] += lazy[idx] * (r - l + 1);
        if (l != r)
            lazy[idx * 2 + 1] += lazy[idx], lazy[idx * 2 + 2] += lazy[idx];
        lazy[idx] = 0;
    }
 
    void _update(ll l, ll r, ll L, ll R, ll idx, ll val) {
        push(idx, l, r);
        if (r < L || l > R)
            return;
        if (l >= L && r <= R) {
            lazy[idx] += val;
            push(idx, l, r);
            return;
        }
        ll mid = (l + r) / 2;
        _update(l, mid, L, R, idx * 2 + 1, val);
        _update(mid + 1, r, L, R, idx * 2 + 2, val);
        tree[idx] = tree[idx * 2 + 1] + tree[idx * 2+ 2];
    }
 
    void update(ll l, ll r, ll val) {
        _update(0, n - 1, l, r, 1, val);
    }
 
    void _set(ll l, ll r, ll L, ll R, ll idx, ll val) {
        push(idx, l, r);
        if (r < L || l > R)
            return;
        if (l >= L && r <= R) {
            sett[idx] = val, lazy[idx] = 0;
            push(idx, l, r);
            return;
        }
        ll mid = (l + r) / 2;
        _set(l, mid, L, R, idx * 2 + 1, val);
        _set(mid + 1, r, L, R, idx * 2 + 2, val);
        tree[idx] = tree[idx * 2 + 1] + tree[idx * 2+ 2];
    }
 
    void set(ll l, ll r, ll val) {
        _set(0, n - 1, l, r, 1, val);
    }
 
    ll _query(ll l, ll r, ll L, ll R, ll idx) {
        push(idx, l, r);
        if (r < L || l > R)
            return 0;
        if (l >= L && r <= R)
            return tree[idx];
        ll mid = (l + r) / 2;
        ll sum = _query(l, mid, L, R, idx * 2 + 1) + 
                 _query(mid + 1, r, L, R, idx * 2 + 2);
        tree[idx] = tree[idx * 2 + 1] + tree[idx * 2 + 2];
        return sum;
    }
 
    ll query(ll l, ll r) {
        return _query(0, n - 1, l, r, 1);
    }
};

vector<ll> deg, par, hei;
vector<vector<ll> > tree, begs, num_chain;
vector<ll> dfsarr, L, R;
 
void dfs(ll a) {
    L[a] = dfsarr.size();
    dfsarr.push_back(a);
    for (ll b : tree[a])
    {
        hei[b] = hei[a] + 1;
        dfs(b);
        begs[a].push_back(L[b]);
        num_chain[a].push_back(0);
    }
    R[a] = dfsarr.size() - 1;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    ll t, x;
    cin >> t >> x;
    while (t--) {
        ll n;
        cin >> n;
        n++;
        tree = begs = num_chain = vector<vector<ll> > (n + 1);
        deg = par = L = R = hei = vector<ll> (n + 1);
        dfsarr.clear();
        for (ll i = 2; i <= n; i++) {
            cin >> par[i];
            tree[par[i]].push_back(i);
        }
        for (ll i = 1; i <= n; i++)
            sort(all(tree[i]));
        dfs(1);
        
        vector<vector<ll> > curr_tree(n + 1);
        ll out = 1, sum1 = 1;
        seggy seg(vector<ll>(n + 1, 1));
        for (ll i = 2; i <= n; i++) {
            deg[par[i]]++;
            deg[i]++;
            ll node_par = seg.query((ll)L[i], (ll)L[i]);

            // no breakage
            if (deg[par[i]] == 2 || par[i] == node_par) {
                ll idx_of_chain = upper_bound(all(begs[node_par]), L[i]) - begs[node_par].begin() - 1;
                if (node_par == 1 and (deg[1] <= 2 || deg[1] == 3 and par[i] == 1)) {
                    num_chain[node_par][idx_of_chain]++;
                    if (deg[1] <= 2) {
                        out -= (sum1 + 1) / 2;
                        sum1++;
                        out += (sum1 + 1) / 2; 
                    } else {
                        out -= (sum1 + 1) / 2;
                        for (ll i = 0; i < tree[1].size(); i++)
                            out += (num_chain[1][i] + 1) / 2;
                    }
                } else {
                    out -= (num_chain[node_par][idx_of_chain] + 1) / 2;
                    num_chain[node_par][idx_of_chain]++;
                    out += (num_chain[node_par][idx_of_chain] + 1) / 2;
                }
                
            } else {
                ll idx_of_chain_og = upper_bound(all(begs[node_par]), L[i]) - begs[node_par].begin() - 1;
                ll new_par = par[i];
                seg.set(L[new_par], R[new_par], new_par);
                ll idx_of_chain = upper_bound(all(begs[new_par]), L[i]) - begs[new_par].begin() - 1;
                num_chain[new_par][idx_of_chain]++;
                out++;

                ll len_of_og_chain = num_chain[node_par][idx_of_chain_og];
                ll len_left = hei[par[i]] - hei[node_par] - 1;
                ll my_len = len_of_og_chain - len_left - 1;

                ll other_node = curr_tree[new_par][0];
                ll other_node_idx = upper_bound(all(begs[new_par]), L[other_node]) - begs[new_par].begin() - 1;

                num_chain[new_par][other_node_idx] += my_len;
                out += (my_len + 1) / 2;

                if (node_par == 1 and deg[1] <= 2) {
                    ll len_lost = num_chain[node_par][idx_of_chain_og] - len_left;
                    out -= (sum1 + 1) / 2;
                    sum1 -= len_lost;
                    num_chain[node_par][idx_of_chain_og] = len_left;
                    out += (sum1 + 1) / 2;
                } else {
                    out -= (num_chain[node_par][idx_of_chain_og] + 1) / 2;
                    num_chain[node_par][idx_of_chain_og] = len_left; // to do effect
                    out += (num_chain[node_par][idx_of_chain_og] + 1) / 2;
                }
            }
            curr_tree[par[i]].push_back(i);

            if (x == 1)
                cout << out << "\n";
        }
        if (x == 0)
            cout << out << "\n";
    }
}

