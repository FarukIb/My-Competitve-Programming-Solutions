#include <bits/stdc++.h>
#define all(a) a.begin(), a.end()
#define mp make_pair

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

vector<vector<int> > og_edges;
vector<vector<int> > rev_og;

vector<vector<int> > sm_graph;

// making new graph
vector<vector<int> > comp_niz;
vector<int> comp;
vector<int> roots;

vector<bool> visited;
bool ok = true;
void dfs(int curr, int root) {
    if (visited[curr]) {
        ok = false;
        return;
    }
    visited[curr] = true;
    comp[curr] = root;
    comp_niz[root].push_back(curr);
    for (int a : rev_og[curr])
        dfs(a, root);
}

vector<pii> edges;
void add_edge(int cf, int ct) { 
    int i = cf;
    int pnt = 0;
    for (int j : comp_niz[ct]) {
        while (pnt < sm_graph[i].size() and sm_graph[i][pnt] < j)
            pnt++;
        if (pnt == sm_graph[i].size() || sm_graph[i][pnt] != j) {
            edges.emplace_back(i, j);
            return;
        }
    }
}

// actual stuff
vector<vector<int> > dont_graph; // this is rev graph
vector<set<int> > dont_graph2; // this is not rev graph

void dfs2(int u, vector<int> &topo, set<int> &un_vis, vector<bool> &visited) {
    un_vis.erase(u);
    if (un_vis.empty()) {
        topo.push_back(u);
        return;
    } 
    auto it = un_vis.begin();
    while (true) {
        int v = *it;
        if (dont_graph2[u].find(v) == dont_graph2[u].end()) dfs2(v, topo, un_vis, visited);
        it = un_vis.upper_bound(v);
        if (it == un_vis.end()) break;
    }
    topo.push_back(u);
}

int get_root() {
    vector<bool> visited(dont_graph.size());
    vector<int> topo_sort;

    set<int> un_vis;
    for (int j : roots)
        un_vis.insert(j);
    
    while (!un_vis.empty()) {
        int me = *un_vis.begin();
        dfs2(me, topo_sort, un_vis, visited);
    }

    return topo_sort.back();
}

void bfs(int c) {
    list<int> un_vis;
    for (int j : roots)
        if (j != c)
            un_vis.push_back(j);
    
    queue<int> q;
    q.push(c);
    stack<list<int>::iterator> to_er;
    while (!q.empty()) {
        int pnt = 0;
        int curr = q.front(); q.pop();
        
        for (auto mei = un_vis.begin(); mei != un_vis.end(); mei++) {
            int me = *mei;
            while (pnt < dont_graph[curr].size() and dont_graph[curr][pnt] < me)
                pnt++;

            if (pnt == dont_graph[curr].size() || dont_graph[curr][pnt] != me) {
                to_er.push(mei);
                q.push(me);
                add_edge(me, curr);
            }
        }
        while (!to_er.empty()) {
            un_vis.erase(to_er.top());
            to_er.pop();
        }
    }
    
}



int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int n, m, k;
    cin >> n >> m >> k;
    og_edges.resize(n);
    rev_og.resize(n);
    dont_graph.resize(n);
    dont_graph2.resize(n);
    sm_graph.resize(n);

    vector<pii> musts;
    for (int i = 0; i < m; i++) 
    {
        int f, t;
        cin >> f >> t;
        musts.push_back(pii(f, t));
        og_edges[f].push_back(t);
        rev_og[t].push_back(f);
        
        if (og_edges[f].size() > 1)
            ok = false;
    }
    
    vector<pii> nono;
    for (int i = 0; i < k; i++) {
        int f, t;
        cin >>f >> t;
        sm_graph[f].push_back(t);
        nono.emplace_back(f, t);
    }

    if (!ok) {
        cout << "NO\n";
        return 0;
    }

    comp.resize(n);
    comp_niz.resize(n);

    visited.resize(n, false);
    // getting graph
    for (int i = 0; i < n; i++)
    {
        if (!og_edges[i].empty())
            continue;
        roots.push_back(i);
        dfs(i, i);
        sort(all(comp_niz[i]));
    }

    if (!ok || count(all(visited), false) > 0) {
        cout << "NO\n";
        return 0;
    }
    
    map<pii, int> cnt;
    for (auto [f, t] : nono) {
        if (comp[f] == comp[t])
            continue;
        if (comp[f] != f)
            continue;
        cnt[pii(f, comp[t])]++;
    }   

    for (auto [pa, cn] : cnt) {
        if (cn == comp_niz[pa.second].size()) {
            dont_graph[pa.second].push_back(pa.first);
            dont_graph2[pa.second].insert(pa.first);
        }
    }
    for (int j : roots)
        sort(all(dont_graph[j]));

    // actually doing the thing
    
    for (int i = 0; i < n; i++)
    {
        sort(all(dont_graph[i]));
        sort(all(sm_graph[i]));
    }

    int root = get_root();
    edges.clear();
    bfs(root);
        
    if (edges.size() != roots.size() - 1)
        cout << "NO\n";
    else
    {
        for (pii a : musts)
            cout << a.first << " " << a.second << "\n";
        for (pii a : edges)
            cout << a.first << " " << a.second << "\n";
    }
}