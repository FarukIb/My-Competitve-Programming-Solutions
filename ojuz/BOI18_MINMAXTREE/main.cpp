#include <bits/stdc++.h>
#define mp make_pair
#define all(a) a.begin(), a.end()

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

const int K = 20;

struct segment {
    int lo, hi, val, height;

    bool operator<(const segment& b) const {
        return height < b.height;
    }
};

vector<vector<int> > tree;
vector<vector<int> > par;

vector<int> inn, outt, height;

int tim = 0;
void dfs(int curr) {
    inn[curr] = tim;
    for (int a : tree[curr]) {
        if (a == par[0][curr])
            continue;
        par[0][a] = curr; tim++; height[a] = height[curr] + 1;
        dfs(a);
    }
    for (int i = 1; i < K; i++)
        par[i][curr] = par[i - 1][par[i - 1][curr]];
    outt[curr] = tim;
}

bool is_anc(int anc, int p) {
    return inn[p] <= inn[anc] and outt[p] >= outt[anc];
}

int lca(int a, int b) {
    if (height[a] > height[b])
        swap(a, b);
    if (is_anc(b, a))
        return a;
    for (int i = K - 1; i >= 0; i--) {
        if (is_anc(a, par[i][b]))
            continue;
        b = par[i][b];
    }
    return par[0][b];
}

vector<int> weight;

void place(int curr, int dest, int val) {
    if (weight[curr] != 0 || curr == dest)
        return;
    weight[curr] = val;
    place(par[0][curr], dest, val);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int n;
    cin >> n;
    inn = outt = height = weight = vector<int>(n + 1); outt[0] = 1e9;
    par = vector<vector<int> >(K, vector<int>(n + 1));
    tree = vector<vector<int> >(n + 1);
    for (int i = 1; i < n; i++) {
        int f, t;
        cin >>f >> t;
        tree[f].push_back(t);
        tree[t].push_back(f);
    }
    dfs(1);

    vector<segment> segs;
    int q;
    cin >> q;
    while (q--) {
        char T;
        cin >> T;
        int f, t, v;
        cin >> f >> t >> v;
        if (height[f] > height[t])
            swap(f, t);
        int lc = lca(f, t);
        if (lc == f)
            segs.push_back({f, t, v, height[f]});
        else {
            segs.push_back({lc, f, v, height[lc]});
            segs.push_back({lc, t, v, height[lc]});
        }
    }
    sort(all(segs));
    for (segment s : segs)
        place(s.hi, s.lo, s.val);
    for (int i = 2; i <= n; i++)
        cout << i << " " << par[0][i] << " " << (weight[i] == 0 ? 1 : weight[i]) << "\n";
}