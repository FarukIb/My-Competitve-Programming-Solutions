#include <vector>
#include "glolib.h"
#include <bits/stdc++.h>
#define mp make_pair
#define all(a) a.begin(), a.end()

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

const int ENEMY = 2;
const int MY = 1;
const int EMPTY = 0;

const int K = 20;

int n;
vector<int> col; 
vector<bool> isleaf;
vector<vector<int> > graph;
set<int> leaves;
vector<vector<int> > par;
vector<set<int> > leftt;

void dfs(int curr) {
    for (int i = 1; i < K; i++)
        par[i][curr] = par[i - 1][par[i - 1][curr]];
    for (int a : graph[curr]) {
        dfs(a);
        leftt[curr].insert(a);
    }

    if (graph[curr].empty())
    {
        leaves.insert(curr);
        isleaf[curr] = true;
    }
}

int mark(int curr, int c) {
    if (col[curr] != EMPTY)
        return curr;
    col[curr] = c;
    leftt[par[0][curr]].erase(curr);
    return mark(par[0][curr], c);
}

int rand_move() {
    mark(*leaves.begin(), MY);
    int val = *leaves.begin();
    leaves.erase(val);
    return val;
}

int find_first_mine(int guy) {
    int c = guy;
    for (int k = K - 1; k >= 0; k--) {
        int curr = par[k][c];
        if (col[curr] != MY)
            c = curr;
    }
    return par[0][c];
}

int trace_guy_for_vote(int curr) {
    if (isleaf[curr])
    {
        leaves.erase(curr);
        mark(curr, MY);
        return curr;
    }
    int val = *leftt[curr].begin();
    leftt[curr].erase(val);
    return trace_guy_for_vote(val);
}

void play_game() {
    int l = rand_move();
    while (1) {
        int response = ruch(l);
        leaves.erase(response);
        mark(response, ENEMY);

        int first_mine = find_first_mine(response);
        if (leftt[first_mine].empty())
            l = rand_move();
        else {
            l = trace_guy_for_vote(first_mine);
        }
    }
}

int main() {
    n = daj_n();
    
    graph.resize(n+1);
    isleaf.resize(n+1);
    leftt.resize(n+1);
    col.resize(n+1);
    par.resize(K, vector<int>(n+1));
    col[0] = MY;
    
    for(int i = 2; i <= n; i++) {
        par[0][i] = daj_przelozonego(i);
        graph[par[0][i]].push_back(i);
    }
    dfs(1);
    play_game();
}
