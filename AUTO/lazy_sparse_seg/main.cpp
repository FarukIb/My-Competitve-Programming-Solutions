#include <bits/stdc++.h>
#define mp make_pair
#define all(a) a.begin(), a.end()

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

struct node {
    int ver;
    ll val;
    ll lazy;
    node* l;
    node* r;
    node() {l = nullptr, r = nullptr, val = 0, lazy = 0, ver = 0;}
};

node* copy_node(node* tocop, int ver) {
    node *neww = new node();
    neww->l = tocop->l;
    neww->r = tocop->r;
    neww->val = tocop->val;
    neww-> lazy = tocop->lazy;
    neww->ver = ver;
    return neww;
}

void push(node* nod, node *pret, int l, int r) {
    if (nod->lazy != 0) {
        nod->val += nod->lazy * (ll)(r - l  + 1);
        if (l != r) {
            if (nod->l == nullptr || nod->l->ver != nod->ver)
                nod->l = copy_node(pret->l, nod->ver);
            if (nod->r == nullptr || nod->r->ver != nod->ver)
                nod->r = copy_node(pret->r, nod->ver);
            nod->l->val += nod->lazy;
            nod->r->val += nod->lazy;
        }
        nod -> lazy = 0;
    }
}

ll query(node *nod, node *pret, int l, int r, int L, int R) {
    push(nod, pret, l, r);
    if (l >= L and r <= R)
        return nod->val;
    if (l > R || r < L) 
        return 0;
    int mid = (l + r) / 2;
    ll out = query(nod->l, pret, l, mid, L, R) + query(nod->r, pret, mid + 1, r, L, R);
    nod->val = nod->l->val + nod->r->val;
    return out;
}

bool bad_range(int &l, int &r, int &L, int &R) {
    return l > R ||r < L;
}

void update(node *nod, node *pret, int l, int r, int L, int R, ll up) {
    push(nod, pret, l, r);
    if (l >= L and r <= R)
    {
        nod->lazy += up;
        push(nod, pret, l, r);
        return;
    }
    if (l > R || r < L)
        return;
    int mid = (l + r) / 2;
    if (!bad_range(l, mid, L, R)) {
        if (nod->l == nullptr || nod->l->ver != nod->ver)
            nod->l = copy_node(pret->l, nod->ver);
        update(nod->l, pret->l, l, mid, L, R, up);
    } else if (nod->l == nullptr)
        nod->l = pret->l;
    mid++;
    if (!bad_range(mid, r, L, R)) {
        if (nod->r == nullptr || nod->r->ver != nod->ver)
            nod->r = copy_node(pret->r, nod->ver);
        update(nod->r, pret->r, mid, r, L, R, up);
    } else if (nod ->r == nullptr)
        nod->r = pret->r;
    
    nod->val = nod->l->val + nod->r->val;
}

void build(int l, int r, node *nod, vector<ll> &arr) {
    if (l == r) {
        nod->val = arr[l];
        return;
    }
    int mid = (l + r) / 2;
    nod->l = new node();
    nod->r = new node();
    build(l, mid, nod->l, arr);
    build(mid + 1, r, nod->r, arr);
    nod->val = nod->l->val + nod->r->val;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int n;
    cin >> n;
    vector<ll> arr(n);
    for (int i = 0; i < n; i++)
        cin >> arr[i];
    vector<node*> roots = {new node()};
    build(0, n - 1, roots[0], arr);
    vector<node*> pars = {roots[0]};
    int q;
    cin >> q;
    while (q--) {
        char op;
        cin >> op;
        if (op == 'q') {
            int ver, l, r;
            cin >> ver >> l >> r;
            cout << query(roots[ver], pars[ver], 0, n - 1, l, r) << "\n";
        } else if (op == 'u') {
            int ver, l, r, up;
            cin >> ver >> l >> r >> up;
            roots.push_back(new node());
            pars.push_back(roots[ver]);
            roots[roots.size() - 1]->ver = roots.size() - 1;
            update(roots.back(), roots[ver], 0, n - 1, l, r, up);
        }
    }
}