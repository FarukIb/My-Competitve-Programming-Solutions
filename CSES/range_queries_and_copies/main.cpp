#include <bits/stdc++.h>
#define mp make_pair
#define all(a) a.begin(), a.end()

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

struct node {
    ll val;
    node *l, *r;

    node() {val = 0, l = nullptr, r = nullptr;}
    node(node *L, node *R, ll v) {l = L, r = R, val = v;}
};

vector<ll> arr;
vector<node*> verzije;

void build(node* curr, int l, int r) {
    if (l == r) {
        curr->val = arr[l];
        return;
    }
    int mid = (l + r) / 2;
    curr->l = new node(), curr->r = new node();
    build(curr->l, l, mid);
    build(curr->r, mid + 1, r);
    curr->val = curr->l->val + curr->r->val;
}

void update(node *pret, node* tren, int l, int r, int idx, ll v) {
    if (l == r) {
        tren->val = v;
        return;
    }
    int mid = (l + r) / 2;
    if (idx <= mid)
    {
        tren->l = new node();
        tren->r = pret->r;
        update(pret->l, tren->l, l, mid, idx, v);
    } else {
        tren->l = pret->l;
        tren->r = new node();
        update(pret->r, tren->r, mid + 1, r, idx, v);
    }
    tren->val = tren->l->val + tren->r->val;
}

ll query(node* curr, int l, int r, int L, int R) {
    if (l > R || r < L)
        return 0;
    if (l >= L and r <= R)
        return curr->val;
    int mid = (l + r) / 2;
    return query(curr->l, l, mid, L, R) + query(curr->r, mid + 1, r, L, R);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int n, q;
    cin >> n >> q;
    verzije.push_back(new node());
    arr.resize(n);
    for (int i = 0; i < n; i++)
        cin >> arr[i];
    vector<node*> kniz = {new node()};
    build(kniz[0], 0, n - 1);
    while (q--) {
        int t;
        cin >>t;
        if (t == 1) {
            node *neww_ver = new node();
            int k, idx, val;
            cin >> k >> idx >> val;
            k--;
            idx--;
            update(kniz[k], neww_ver, 0, n - 1, idx, val);
            kniz[k] = neww_ver;
        } else if (t == 2) {
            int k, l, r;
            cin >> k >> l >> r;
            l--, r--;
            cout << query(kniz[k-1], 0, n - 1, l, r) << "\n";
        } else {
            int k;
            cin >> k;
            k--;
            kniz.push_back(kniz[k]);
        }
    }
}