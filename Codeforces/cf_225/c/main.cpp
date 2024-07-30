#include <bits/stdc++.h>
#define mp make_pair

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

struct seggy {
    int n;
    vector<int> tree;

    seggy(vector<int> arr) {
        n = arr.size();
        tree.resize(n * 2, 0);

        for (int i = 0; i < n; i++)
            tree[i + n] = arr[i];
        for (int i = n - 1; i > 0; i--)
            tree[i] = tree[i * 2 + 1] + tree[i * 2];
    }
    
    int query(int idx) {
        int val = 0;
        for (idx += n; idx > 0; idx /= 2)
            val += tree[idx];
        return val;
    }

    void mod(int l, int r, int val) {
        for (l += n, r += n+1; l < r; l /= 2, r /= 2) {
            if (l & 1)
                tree[l++] += val;
            if (r & 1)
                tree[--r] += val;
        }
    }
};

vector<int> height;
vector<int> num_children;
vector<int> idxs;

vector<int> dfsarr;
void dfs(int curr, int par, int hght, vector<vector<int> > &graph) {
    height[curr] = hght;
    idxs[curr] = dfsarr.size();
    dfsarr.push_back(curr);
    num_children[curr] = 1;
    for (int s : graph[curr])
    {
        if (s != par)
        {
            dfs(s, curr, hght + 1, graph);
            num_children[curr] += num_children[s];
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int n, m;
    cin >> n >> m;
    vector<int> a(n);
    height.resize(n, 0);
    num_children.resize(n, 0);
    idxs.resize(n, 0);
    for (int i = 0; i < n; i++)
        cin >> a[i];
    vector<vector<int> > graph(n);
    for (int i = 1; i < n; i++) {
        int f, t;
        cin >> f >> t;
        f--, t--;
        graph[f].push_back(t);
        graph[t].push_back(f);
    }

    dfs(0, -1, 0, graph);
    seggy even_seg(vector<int>(n, 0));
    seggy odd_seg(vector<int>(n, 0));
    
    while (m--) {
        int t;
        cin >>t;
        if (t == 2) {
            int x;
            cin >>x;
            x--;
            if (height[x] % 2 == 0) {
                cout << a[x] + even_seg.query(idxs[x]) << "\n";
            } else {
                cout << a[x] + odd_seg.query(idxs[x]) << "\n";
            }
        } else {
            int x, val;
            cin >> x >> val;
            x--;
            if (height[x] % 2)
                val = -val;
            even_seg.mod(idxs[x], idxs[x] + num_children[x] - 1, val);
            odd_seg.mod(idxs[x], idxs[x] + num_children[x] - 1, -val);
        }
    }
}