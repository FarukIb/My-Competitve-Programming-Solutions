#include <bits/stdc++.h>
#define mp make_pair
#define all(a) a.begin(), a.end()

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

const int maxn = 2e5 + 1;

int seg[maxn*4];

int niz[maxn];
void build(int l, int r, int idx) {
    if (l == r) {
        seg[idx] = niz[l];
        return;
    }
    int mid = (l + r) / 2;
    build(l, mid, idx * 2);
    build(mid + 1, r, idx * 2 + 1);
    seg[idx] = seg[idx * 2] + seg[idx * 2 + 1];
}

int query(int l, int r, int L, int R, int idx) {
    if (l > R ||r < L)
        return 0;
    if (l >= L and r <= R)
        return seg[idx];
    int mid = (l + r) / 2;
    return query(l, mid, L, R, idx * 2) + query(mid + 1, r, L, R, idx * 2 + 1);
}

void mod(int l, int r, int idx, int i, int val) {
    if (l < i || r > i)
        return;
    if (l == i and r == i) {
        seg[idx] += val;
        return;
    }
    int mid = (l + r) / 2;
    mod(l, mid, idx * 2, i, val);
    mod(mid + 1, r, idx * 2 + 1, i, val);
    seg[idx] = seg[idx * 2] + seg[idx * 2 + 1];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    // suma na intervalu
    // modificirati vrijednost
    
}