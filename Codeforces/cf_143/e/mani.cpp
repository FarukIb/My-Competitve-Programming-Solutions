#include <bits/stdc++.h>
#define mp make_pair

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

const ll mod = 1e9 + 7;

struct seggy {
    vector<pii> tree;
    int n;
    seggy(vector<pii> arr) {
        n = arr.size();
        tree.resize(2 * n);
        for (int i = 0; i < n; i++)
            tree[i + n] = arr[i];
        for (int i = n - 1; i > 0; i--)
            tree[i] = min(tree[i * 2], tree[i * 2 + 1]);
    }

    int query(int l, int r) {
        pii mini(1e9, 1e9);
        for (l += n, r += n + 1; l < r; l /= 2, r /= 2) {
            if (l & 1)
                mini = min(mini, tree[l++]);
            if (r & 1)
                mini = min(mini, tree[--r]);
        }
        return mini.second;
    }
};

// GRAPH 1 PROCESSING

vector<vector<int> > graph;
vector<int> par1;
vector<int> phase;

vector<int> whatcycle;
int cyc_number = 1;
void dfs1(int curr, int par) {
    if (phase[curr] == 1) {
        whatcycle[curr] = cyc_number;
        int guy = par;
        while (guy != curr) {
            whatcycle[guy] = cyc_number;
            guy = par1[guy];
        }
        cyc_number++;
        return;
    }
    else if (phase[curr] == 2)
        return;
    phase[curr] = 1;
    par1[curr] = par;
    for (int x : graph[curr])
        if (x != par)
            dfs1(x, curr);
    phase[curr] = 2;
}

// TREE PROCESSING

vector<bool> iscyc;
vector<vector<int> > tree;

vector<int> num_on_path_to_root;
vector<int> par;
vector<pii> seg_arr;
int tim = 0;
vector<int> enter_idx;
void dfs(int curr, int num_spec, int hght) {
    num_on_path_to_root[curr] = num_spec;
    tim++;
    enter_idx[curr] = tim;
    seg_arr.push_back(mp(curr, hght));
    for (int x : tree[curr]) {
        if (x == par[curr])
            continue;
        par[x] = curr;
        dfs(x, num_spec + (int)iscyc[x], hght + 1);
    }
    seg_arr.push_back(mp(curr, hght));
}

int LCA(int a, int b, seggy &seg) {
    return seg.query(min(enter_idx[a], enter_idx[b]), max(enter_idx[a], enter_idx[b]));
}



int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int n, m;
    cin >> n >> m;
    graph.resize(n + 1);
    par1.resize(n + 1, 0);
    phase.resize(n + 1, 0);
    whatcycle.resize(n + 1, 0);

    for (int i = 0; i < m; i++) {
        int f, t;
        cin >> f>> t;
        graph[f].push_back(t);
        graph[t].push_back(f);
    }
    dfs1(1, -1);

    int t_size = cyc_number - 1;
    tree.resize(n + t_size + 1);
    num_on_path_to_root.resize(n + t_size + 1, 0);
    par.resize(n + t_size + 1);
    iscyc.resize(n + t_size + 1);

    vector<int> vertices; // used just for finding any vertex
    for (int i = 1; i <= n; i++) {
        if (whatcycle[i] != 0)
            iscyc[n + whatcycle[i]] = true, vertices.push_back(n + whatcycle[i]);
        else
            vertices.push_back(i);
        for (int x : graph[i]){
            int rep = x;
            if (whatcycle[x] != 0)
                rep = whatcycle[x] + n;
            if (whatcycle[i] == 0) {
                tree[i].push_back(rep);
            }
            else {
                if (rep != whatcycle[i] + n)
                    tree[whatcycle[i] + n].push_back(rep);
            }
        }
    }

    int root = *vertices.begin();
    dfs(root, (int)iscyc[root], 0);

    vector<ll> powers_of_2(n + 1, 1);
    for (int i = 1; i <= n; i++)
        powers_of_2[i] = (powers_of_2[i - 2] * 2) % mod;
    while (m--) {
        
    }
}