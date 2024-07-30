#include <bits/stdc++.h>
#define mp make_pair
#define all(a) a.begin(), a.end()

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

struct node;

node *dummy_node;
struct node {
    node *l, *r;
    int sum;
    node() {l = dummy_node, r = dummy_node;}
};

int query(int l, int r, int L, int R, node *nod) {
    if (r < L || l > R || nod->sum == 0)
        return 0;
    if (l >= L and r <= R)
        return nod->sum;
    int mid = (l + r) / 2;
    return query(l, mid, L, R, nod->l) +
    query(mid + 1, r, L, R, nod->r);
}  

void mod(int l, int r, int idx, int val, node *nod) {
    if (l == r) {
        nod->sum += val;
        return;
    }
    int mid = (l + r) / 2;
    if (idx <= mid) {
        if (nod->l == dummy_node)
            nod->l = new node();
        mod(l, mid, idx, val, nod->l);
    } else {
        if (nod->r == dummy_node)
            nod->r = new node();
        mod(mid + 1, r, idx, val, nod->r);
    }
    nod->sum += val;
}

const int maxn = 1e9+1;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    dummy_node = new node();
    dummy_node->l = dummy_node->r = dummy_node;
    int n, q;
    cin >> n >> q;
    node *root = new node();
    vector<int> arr(n);
    for (int i = 0; i < n; i++) {
        cin >>arr[i];
        mod(0, maxn, arr[i], 1, root);
    }

    while (q--) {
        char o;
        cin >> o;
        if (o == '?') {
            int a, b;
            cin >> a >> b;
            cout << query(0, maxn, a, b, root) << "\n";
        } else {
            int idx, nv;
            cin >> idx >> nv; idx--;
            mod(0, maxn, arr[idx], -1, root);
            arr[idx] = nv;
            mod(0, maxn, arr[idx], 1, root);
        }
    }
}