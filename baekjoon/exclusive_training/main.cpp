#include <bits/stdc++.h>
#define mp make_pair
#define all(a) a.begin(), a.end()

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

struct node {
    ll max_sum, max_moguce;
    node() {max_sum = 0, max_moguce = 0;}
    node(ll a, ll b) {max_sum = a, max_moguce = b;}
};
node merge(node a, node b) {
    return node(max(a.max_sum, b.max_sum), max(a.max_moguce, b.max_moguce));
}

node merge2(node a, node b) {
    return node(a.max_sum + b.max_sum, max(a.max_moguce, a.max_sum + b.max_moguce));
}

struct seggy {
    vector<node> tree;
    vector<node> lazy;
    int n;

    seggy(int siz) {
        n = siz;
        tree.resize(n*4);
        lazy.resize(n*4);
    }

    void push(int idx, int l, int r) {
        tree[idx] = merge2(tree[idx], lazy[idx]);
        if (l != r)
            lazy[idx*2] = merge2(lazy[idx*2], lazy[idx]), lazy[idx*2+1] = merge2(lazy[idx*2+1], lazy[idx]);
        lazy[idx] = node(0, 0);
    }

    void update(int l, int r, int L, int R, int idx, ll val) {
        push(idx, l, r);
        if (l > R || r < L)
            return;
        if (l >= L and r <= R) {
            lazy[idx] = merge2(lazy[idx], node(val, max(0LL, val)));
            push(idx, l, r);
            return;
        }
        int mid = (l + r) / 2;
        update(l, mid, L, R, idx*2, val);
        update(mid + 1, r, L, R, idx*2+1, val);
        tree[idx] = merge(tree[idx*2], tree[idx*2+1]);
    }

    void update(int l, int r, ll val) {update(0, n - 1, l, r, 1, val);}

    node query(int l, int r, int L, int R, int idx) {
        push(idx, l, r);
        if (l > R || r < L)
            return node();
        if (l >= L and r <= R)
            return tree[idx];
        int mid = (l + r) / 2;
        node curr = merge(query(l, mid, L, R, idx*2), query(mid + 1, r, L, R, idx*2+1));
        tree[idx] = merge(tree[idx*2], tree[idx*2+1]);
        return curr;
    }

    node query(int l, int r) {return query(0, n - 1, l, r, 1);}
};

struct person {
    int rating, p, a, b, idx;
    person() {}
};

int cmp(person a, person b) {return a.rating < b.rating;}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int n;
    cin >> n;
    vector<person> people(n);
    int maxd = 0;
    for (int i = 0; i < n; i++) 
    {
        cin >> people[i].rating >> people[i].p >> people[i].a >> people[i].b;
        people[i].idx = i;
        maxd = max(maxd, people[i].b);
    }
    sort(all(people), cmp);
    seggy seg(maxd + 1);
    vector<ll> ans(n);
    for (int i = 0; i < n; i++) {
        ans[people[i].idx] = people[i].p + seg.query(people[i].a, people[i].b).max_moguce;
        seg.update(people[i].a, people[i].b, people[i].p);
    }
    for (ll a : ans)
        cout << a << "\n";
}