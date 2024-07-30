#include <bits/stdc++.h>

using namespace std;

int cnt = 0;
bool ask(int x) {
    cnt++;
	printf("? %d ", x);
	fflush(stdout);
	int res;
	int ignore = scanf("%d", &res);
	return res;
}

vector<int> initt;
bool myask(int curr) {
    if (initt[curr] != -1)
        return initt[curr];
    return initt[curr] = (int)ask(curr);
}

int n;
vector<int> par;
vector<vector<int> > graph;
vector<int> subt_size;
vector<bool> marked;
vector<bool> visited;

int num = 0;
void get_subt_size(int curr, int par) {
    num++;
    subt_size[curr] = 1;
    for (int a : graph[curr]) {
        if (a == par || marked[a])
            continue;
        get_subt_size(a, curr);
        subt_size[curr] += subt_size[a];
    }
}

int get_centroid(int curr, int par, int size_of_subtree) {
    for (int a : graph[curr]) 
        if (subt_size[a] * 2 > size_of_subtree and curr != par and !marked[a])
            return get_centroid(a, curr, size_of_subtree);
    return curr;
}

int search(int curr, int pa) {
    num = 0;
    get_subt_size(curr, -1);
    int cent = get_centroid(curr, pa, subt_size[curr]);
    marked[cent] = true;
    if (num == 1)
        return curr;
        
    if (myask(cent)) 
    {
        int someone_in = 0;
        for (int a : graph[cent])
            if (myask(a))
                someone_in = a;
        if (someone_in == 0)
            return cent;
        return search(someone_in, cent);
    }
    return search(curr, pa);
}

int solve(int N, std::vector<int> p){
	n = p.size()+1;
    graph.resize(n+1);
    initt.resize(n+1, -1);
    subt_size.resize(n+1);
    marked.resize(n+1);
    par.resize(n+1);
    for (int i = 2; i <= n; i++)
    {
        graph[p[i - 2]].push_back(i);
        par[i] = p[i - 2];
    }
    
    return search(1, 0);
}

int main() {
    int n, a, b;
	int ignore = scanf("%d", &n);
    std::vector<int>p(n-1);

	for(int i=0;i<n-1;i++){
        ignore = scanf("%d", &p[i]);
	}

	int res = solve(n, p);
	printf("! %d %d", res, cnt);
	fflush(stdout);
}

