#include <bits/stdc++.h>
#define mp make_pair

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

vector<int> comp;
vector<int> arr;

int convert(int val) {
    return lower_bound(comp.begin(), comp.end(), val + 1) - comp.begin() - 1;
}

struct sum_seg {
    vector<int> t;
    int n;

    sum_seg(int L, int R) {
        n = comp.size() + 1;
        t.resize(2 * n, 0);

        for (int i = L; i <= R; i++) {
            t[n + convert(arr[i])]++;
        }
        for (int i = n - 1; i > 0; i--)
            t[i] = t[i * 2 + 1] + t[i * 2];
    }

    void update(int idx, int val) {
        idx = convert(idx);
        for (idx += n; idx > 0; idx /= 2)
            t[idx] += val;
    }

    int query(int r) {
        int l = 0;
        r = convert(r);
        int sum = 0;
        for (l += n, r += n; l < r; l /= 2, r /= 2) {
            if (l & 1)
                sum += t[l++];
            if (r & 1)
                sum += t[--r];
        }
        return sum;
    }
};

vector<sum_seg> bseggy;

const int len = 700;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int n, q;
    cin >> n;
    arr.resize(n, 0);

    vector<int> mannn(1, 0);
    for (int i = 0; i < n; i++)
        cin >> arr[i];

    cin >> q;
    vector<int> q1(q);
    vector<pii> q2(q);
    vector<int> q3(q);
    for (int i = 0; i < q; i++) {
        cin >> q1[i];

        cin >> q2[i].first;
        cin >> q2[i].second;
        if (q1[i] == 0)
        {
            cin >> q3[i];
            mannn.push_back(q3[i]);
        }
    }
    sort(mannn.begin(), mannn.end());

    comp.push_back(0);
    for (int i = 1; i < mannn.size(); i++)
        if (mannn[i] != mannn[i - 1])
            comp.push_back(mannn[i]);
    comp.push_back(2e9);
    
    // SQRT DECOMP
    for (int i = 0; i < len; i++) {
        bseggy.push_back(sum_seg(i * len, min(n - 1, (i + 1) * len - 1)));
    }
    
    for (int t = 0; t < q; t++) {
        if (q1[t] == 0) {
            int l = q2[t].first, r = q2[t].second, c = q3[t];
            l--, r--;

            int l_bucket = l / len;
            int r_bucket = r / len;

            int ans = r - l + 1;
            if (l_bucket == r_bucket) {
                for (int i = l; i <= r; i++)
                    if (arr[i] < c)
                        ans--;
            }
            else {
                for (int i = l; i < min(n, len * (l_bucket + 1)); i++)
                    if (arr[i] < c)
                        ans--;

                for (int j = l_bucket + 1; j < r_bucket; j++)
                    ans -= bseggy[j].query(c);

                for (int i = r_bucket * len; i <= r; i++)
                    if (arr[i] < c)
                        ans--;
            }

            cout << ans << "\n";
        }
        else {
            int p = q2[t].first - 1;
            ll newval = q2[t].second;
            int p_bucket = p / len;
            int old_val = arr[p];
            bseggy[p_bucket].update(old_val, -1);
            bseggy[p_bucket].update(newval, 1);
            arr[p] = newval;
        }
    }
}