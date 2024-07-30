#include <bits/stdc++.h>
#define mp make_pair
#define all(a) a.begin(), a.end()

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

struct node {
    int sum, min_val;
};
void merge_node(node &t, node &a, node &b) {t.sum = a.sum + b.sum, t.min_val = min(b.min_val, a.min_val + b.sum);}

struct seggy{
    vector<node> t; int n;
    seggy(int N) {
        n = pow(2, ceil(log(N)/log(2))); t.resize(2*n, {0, 0});

    }
    int get() {return t[1].min_val;}
    void upd(int idx, int n_val) {
        for (idx += n, t[idx].sum = n_val, t[idx].min_val =  min(0, n_val), idx /= 2; idx > 0; idx /= 2)
            merge_node(t[idx], t[idx*2], t[idx*2+1]);
    }
};

const int K = 500;

bool cmp(pair<pii, int> a, pair<pii, int> b) {
    if (a.first.first / K == b.first.first / K)
        return a.first.second < b.first.second;
    return a.first.first / K < b.first.first / K;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int n;
    cin >> n;
    string s;
    cin >>s;
    vector<int> arr(n);
    vector<int> a(n);
    vector<deque<int> > idxs(n*2+1);
    for (int i = 0; i < n; i++)
    {
        arr[i] = s[i] == 'T' ? -1 : 1;
        a[i] = arr[i];
        if (i != 0)
            arr[i] += arr[i - 1];
    }

    int q;
    cin >> q;
    vector<pair<pii, int>> queries;
    for (int i = 0; i < q; i++) {
        int l, r;
        cin >> l >> r;
        queries.push_back({{l - 1, r - 1}, i});
    }
    sort(all(queries), cmp);
    int l = 0, r = -1, ans1 = 0, bal = 0;

    int prev_sum, first_m1_idx, first_0_idx;
    seggy seg(n);
    vector<int> out(q);

    for (auto &[query, idx] : queries) {
        if (query.first < l) {
            for (l--; l >= query.first; l--) {
                prev_sum = arr[l];
                idxs[arr[l]+n].push_front(l);
                if (a[l] == -1) {
                    ans1++;
                } else {
                    bal++;
                    seg.upd(l, 1);
                    if (n + prev_sum - 1 < 0 || idxs[n + prev_sum - 1].empty())
                        continue;
                    first_m1_idx = idxs[n + prev_sum - 1].front();
                    seg.upd(first_m1_idx, -1);
                    bal--;
                    ans1--;
                }
            }
            l++;
        }

        if (query.second > r) {
            for (r++; r <= query.second; r++) {
                if (a[r] == 1) {
                    seg.upd(r, 1), bal++;
                }
                else {
                    if (bal == 0)
                        ans1++;
                    else
                        seg.upd(r, -1), bal--;
                }
                idxs[arr[r] + n].push_back(r);
            }
            r--;
        }

        if (query.first > l) {
            for (;l < query.first; l++) {
                if (seg.t[seg.n+l].sum != 0)
                    seg.upd(l, 0);
                idxs[arr[l]+n].pop_front();
                prev_sum = l == 0 ? 0 : arr[l - 1];
                if (a[l] == 1)
                {
                    bal--;
                    if (idxs[n + prev_sum].empty())
                        continue;
                    ans1++;
                    first_0_idx = idxs[n + prev_sum].front();
                    seg.upd(first_0_idx, 0);
                    bal++;
                } else
                    ans1--;
            }
        }

        if (query.second < r) {
            for (; r > query.second; r--) {
                idxs[arr[r] + n].pop_back();
                if (a[r] == 1) {
                    seg.upd(r, 0);
                    bal--;
                } else {
                    if (seg.t[r+seg.n].sum == 0)
                        ans1--;
                    else
                        seg.upd(r, 0), bal++;
                }
            }
        }
        out[idx] = -seg.get() + ans1;
    }

    for (int a : out)
        cout <<a << "\n";
    cout << "\n";
}