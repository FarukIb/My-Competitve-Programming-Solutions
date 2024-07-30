#include <bits/stdc++.h>
#define mp make_pair
#define all(a) a.begin(), a.end()

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

struct lazy_seg {
    vector<int>t;
    vector<int> lazy;
    int n;

    lazy_seg(vector<int> arr) {
        n = arr.size();
        t.resize(n*4);
        lazy.resize(n*4);
        build(1, 0, n - 1, arr);
    }
    
    void build(int idx, int l, int r, vector<int> &arr) {
        if (l == r) {
            t[idx] = arr[l];
            return;
        }
        int mid = (l + r) / 2;
        build(idx *2, l, mid, arr);
        build(idx*2+1, mid + 1, r, arr);
        t[idx] = t[idx * 2] + t[idx * 2 + 1];
    }
    
    void push(int idx, int l, int r) {
        t[idx] += (r - l + 1) * lazy[idx];
        if (l != r) 
            lazy[idx * 2] += lazy[idx], lazy[idx * 2 + 1] += lazy[idx];
        lazy[idx] = 0;
    }

    void update(int l, int r, int L, int R, int idx, int val) {
        push(idx, l , r);
        if (l > L || r < L)
            return;
        if (l >= L and r <= R) {
            lazy[idx] += val;
            push(idx, l, r);
            return;
        }
        int mid = (l + r) / 2;
        update(l, mid, L, R, idx * 2, val);
        update(mid + 1, r, L, R, idx * 2 + 1, val);
    }

    void update(int l, int r, int val) { update(0, n - 1, l, r, 1, val); }

    int query(int l, int r, int L, int R, int idx) {
        push(idx, l , r);
        if (l > L || r < L)
            return 0;
        if (l >= L and r <= R)
            return t[idx];
        int mid = (l + r) / 2;
        int out = query(l, mid, L, R, idx * 2) + query(mid + 1, r, L, R, idx * 2 + 1);
        t[idx] = t[idx * 2] + t[idx * 2 + 1];
        return out;
    }

    int query(int l, int r) {return query(0, n - 1, l, r, 1);}
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    
}