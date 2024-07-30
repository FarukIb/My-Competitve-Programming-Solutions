#include "race.h"
#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> pii;

int n, k;
vector<vector<pii> > graph;
vector<bool> marked;
vector<int> sz;
int min_len = 1e9;

int find_centroid(int curr, int par, int all) {
	for (auto &[a, w] : graph[curr])
		if (a != par and !marked[a] and sz[a] * 2 > all)
			return find_centroid(a, curr, all);
	return curr;
}

vector<int> min_length_for_siz;
void reset_mlfs(int curr, int par, int depth) {
	sz[curr] = 0;
	if (depth > k)
		return;
	min_length_for_siz[depth] = 1e9;
	sz[curr] = 1;
	for (auto &[a, w] : graph[curr])
		if (!marked[a] and a != par)
			reset_mlfs(a, curr, depth + w), sz[curr] += sz[a];
}

void update_mlfs(int curr, int par, int depth, int len) {
	if (depth > k)
		return;
	min_length_for_siz[depth] = min(min_length_for_siz[depth], len);
	for (auto &[a, w] : graph[curr])
		if (!marked[a] and a != par)
			update_mlfs(a, curr, depth + w, len + 1);
}

void update_k(int curr, int par, int depth, int len) {
	if (depth > k)
		return;
	min_len = min(min_len, len + min_length_for_siz[k-depth]);
	for (auto &[a, w] : graph[curr])
		if (!marked[a] and a != par)
			update_k(a, curr, depth + w, len + 1);
}

void dfs(int curr) {
	reset_mlfs(curr, 0, 0);
	int cent = find_centroid(curr, 0, sz[curr]);
	marked[cent] = true;
	min_length_for_siz[0] = 0;
	for (auto &[a, w] : graph[cent]) {
		if (marked[a])
			continue;
		update_k(a, cent, w, 1);
		update_mlfs(a, cent, w, 1);
	}
	reset_mlfs(cent, 0, 0);
	for (auto &[a, w] : graph[cent])
		if (!marked[a])
			dfs(a);
}

int best_path(int N, int K, int H[][2], int L[])
{
    n = N;
	k = K;
    graph.resize(n+1);
	marked.resize(n+1);
	sz.resize(n+1);
	min_len = 1e9;
	min_length_for_siz.resize(K+1, 1e9);
	for (int i = 0; i < n - 1; i++) {
		graph[H[i][0]].push_back(pair<int,int>(H[i][1], L[i]));
		graph[H[i][1]].push_back(pair<int,int>(H[i][0], L[i]));
	}
	dfs(1);
	if (min_len == 1e9)
    	return -1;
	return min_len;
}

