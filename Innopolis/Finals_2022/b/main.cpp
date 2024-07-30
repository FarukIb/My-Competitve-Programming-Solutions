#include <bits/stdc++.h>
#define pii pair<int, int>
#define ll long long
#define ld long double

using namespace std;

struct edge {
    int f, t, w, id;
    edge() {

    }

    edge (int F, int T, int W) {
        if (F > T)
            swap(F, T);
        f = F, t = T, w = w;
    }
};

struct UFDS {
    vector<int> ufds;

    UFDS (int _size) {
        ufds.resize(_size + 1);
        for (int i = 0; i <= _size; i++)
            ufds[i] = i;
    }

    int unionFind(int x) {
        if (ufds[x] == x)
            return x;
        return ufds[x] = unionFind(ufds[x]);
    }

    bool connected(int x, int y) {
        return unionFind(x) == unionFind(y);
    }

    void unionJoin(int x, int y)
    {
        if (connected(x, y))
            return;
        ufds[unionFind(x)] = unionFind(y);
    }
};

vector<vector<int> > par;
vector<int> height;
vector<int> ent;
vector<int> leave;
vector<int> upToRoot;
int tim = 0;

vector<vector<pii> > tree;
void getPar(int c, int hght, int sum) {
    upToRoot[c] = sum;
    height[c] = hght;
    ent[c] = tim++;
    for (pii x : tree[c])
    {
        if (c == 1 || x.first != par[c][0]) {
            par[x.first].push_back(c);
            getPar(x.first, hght + 1, sum + x.second);
        }
    }
    leave[c] = tim++;
}

bool isAncestor(int x, int y) {
    return ent[y] <= ent[x] && leave[y] >= leave[x];
}

int lift(int c, int weight) {
    for (int bit = 0; bit <= 20; bit++) {
        if (1 << bit & weight) {
            if (par[c].size() <= bit)
                return -1;
            c = par[c][bit];
        }
    }
    return c;
}

int n;
int lca(int x, int y) {
    if (height[x] < height[y])
        swap(x, y);

    int l = 0, r = n;
    while (l < r) {
        int mid = (l + r) / 2;
        int node = lift(x, mid);

        if (node == -1)
            r = mid;
        else if (isAncestor(x, node) && isAncestor(y, node))
            r = mid;
        else
            l = 1 + mid;
    }

    return lift(x, l);
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int m;
    cin >> n >> m;
    vector<edge> edges(m);
    map<pii, int> mapp; // first = edge, second = id
    for (int i = 0; i < m; i++)
    {
        cin >> edges[i].f >> edges[i].t >> edges[i].w;
        if (edges[i].f > edges[i].t)
            swap(edges[i].f, edges[i].t);
        edges[i].w %= 2;
        edges[i].id = i + 1;
    }

    UFDS ufds(n);
    tree.resize(n + 1);
    vector<edge> newEdges;
    vector<bool> added(m);
    int pnt = 0, sum = 0; int numNodes = 0;
    while (pnt < m) {
        edge curr = edges[pnt++];
        if (ufds.connected(curr.f, curr.t))
        {
            continue;
        }
        numNodes++;
        ufds.unionJoin(curr.f, curr.t);
        added[pnt - 1] = true;


        mapp[pii(curr.f, curr.t)] = pnt - 1;

        tree[curr.f].push_back(pii(curr.t, curr.w));
        tree[curr.t].push_back(pii(curr.f, curr.w));
        sum += curr.w;
        sum %= 2;
        newEdges.push_back(curr);
    }

    if (numNodes < n - 1) {
        cout << "-1\n";
        return 0;
    }
    if (sum == 0) {
        cout << "YES\n" << newEdges[0].id;
        for (int i = 1; i < n - 1; i++) {
            cout << " " << newEdges[i].id;
        }
        cout << "\n";
    }
    else {
        par.resize(n + 1, vector<int>());
        height.resize(n + 1, 0);
        ent.resize(n + 1, 0);
        leave.resize(n + 1, 0);
        upToRoot.resize(n + 1, 0);
        getPar(1, 0, 0);

        // BUILD PAR
        for (int bit = 1; bit <= 20; bit++) {
            for (int i = 1; i <= n; i++) {
                if (par[i].size() < bit)
                    continue;
                if (par[par[i][bit - 1]].size() < bit)
                    continue;
                par[i].push_back(par[par[i][bit - 1]][bit - 1]);
            }
        }

        edge toRemove(-1, -1, -1);
        for (int i = 0; i < m; i++) {
            if (added[i])
                continue;
            edge curr = edges[i];
            if (toRemove.f != -1)
                break;

            int LCA = lca(curr.f, curr.t);
            
            int path1 = upToRoot[curr.f] - upToRoot[LCA];
            if (curr.w == 1)
                path1 = -height[LCA] + height[curr.f] - path1;

            int path2 = upToRoot[curr.t] - upToRoot[LCA];
            if (curr.w == 1)
                path2 = - height[LCA] + height[curr.t] - path2;

            if (path1 > 0) {
                int node = par[curr.f][0], last = curr.f;
                while (height[node] >= height[LCA]) {
                    if (edges[mapp[pii(min(node, last), max(node, last))]].w != curr.w)
                        toRemove = edges[mapp[pii(min(node, last), max(node, last))]];

                    if (node == 1)
                        break;
                    int tmp = node;
                    node = par[node][0];
                    last = tmp;
                }

                edge toAdd = curr;
                newEdges.push_back(toAdd);
                break;
            }
            else if (path2 > 0) {
                int node = par[curr.t][0], last = curr.t;
                while (height[node] >= height[LCA]) {
                    if (edges[mapp[pii(min(node, last), max(node, last))]].w != curr.w)
                        toRemove = edges[mapp[pii(min(node, last), max(node, last))]];

                    if (node == 1)
                        break;
                    int tmp = node;
                    node = par[node][0];
                    last = tmp;
                }

                edge toAdd = curr;
                newEdges.push_back(toAdd);
                break;
            }
        }

        if (toRemove.f == -1)
            cout << "NO\n";
        else {
            cout << "YES\n";
            vector<int> out;
            for (int i = 0; i < n; i++) {
                if (newEdges[i].id == toRemove.id)
                    continue;
                out.push_back(newEdges[i].id);
            }
            sort(out.begin(), out.end());

            cout << out[0];
            for (int i = 1; i < n - 1; i++)
                cout << " " << out[i];
            cout << "\n";
        }
    }
}
