#include <bits/stdc++.h>
#define mp make_pair
#define all(a) a.begin(), a.end()

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

struct seggy {
    int n;
    vector<int> arr;

    seggy() {}
    seggy(int N) {n = N, arr.resize(n*2);}

    void upd(int idx, int v) {
        for (idx += n; idx > 0; idx /=2)
            arr[idx] += v;
    }

    int query(int l, int r) {
        int out = 0;
        for (l += n, r += n + 1; l < r; l/= 2, r /= 2) {
            if (l & 1)
                out += arr[l++];
            if (r & 1)
                out += arr[--r];
        }
        return out;
    }
};

struct query {
    int l, r, idx;

    bool operator<(const query & b) const {
        return l < b.l;
    }
};

int maxi = 0;
vector<query> compress(vector<query> arr) {
    set<int> al;
    for (int i = 0; i < arr.size(); i++)
        al.insert(arr[i].l), al.insert(arr[i].r);
    map<int, int> cnv; int cnt = 0;
    for (int a : al)
        cnv[a] = cnt++;
    maxi = cnt;
    for (int i = 0; i < arr.size(); i++)
        arr[i].l = cnv[arr[i].l], arr[i].r = cnv[arr[i].r];
    sort(all(arr));
    return arr;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int n;
    cin >> n;
    vector<query> queries(n);
    for (int i = 0; i < n; i++) {
        queries[i].idx = i;
        cin >> queries[i].l >> queries[i].r;
    }
    queries = compress(queries);
    seggy sett(maxi);
    vector<vector<query> > qs(maxi);
    for (int i = 0; i < n; i++)
        sett.upd(queries[i].r, 1), qs[queries[i].l].push_back(queries[i]);
    vector<int> contains(n);
    for (int i = 0; i < maxi; i++) {
        for (query q : qs[i])
            contains[q.idx] = sett.query(0, q.r) - 1;
        for (query q : qs[i])
            sett.upd(q.r, -1);
    }

    seggy sett2(maxi);
    vector<int> contained(n);
    for (int i = 0; i < maxi; i++) {
        for (query q : qs[i])
            sett2.upd(q.r, 1);
        for (query q : qs[i])
            contained[q.idx] = sett2.query(q.r, maxi - 1) - 1;
        
    }

    for (int i = 0; i < n; i++)
        cout << min(1, contains[i]) << " ";
    cout << endl;
    for (int j = 0; j < n; j++)
        cout << min(1, contained[j]) << " ";
    cout << endl;
}