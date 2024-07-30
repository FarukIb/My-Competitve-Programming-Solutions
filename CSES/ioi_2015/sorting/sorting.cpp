#include "sorting.h"
#include <bits/stdc++.h>

using namespace std;

vector<bool> visited;
vector<int> s;

void dfs(int curr) {
	if (visited[curr])
		return;
	visited[curr] = true;
	dfs(s[curr]);
}

int numswaps(int *S, int n, int X[], int Y[], int num) {
	visited = vector<bool>(n, false);
	s = vector<int>(n);
	for (int i = 0; i < n; i++)
		s[i] = S[i];
	for (int i = 0; i < num; i++)
		swap(s[X[i]], s[Y[i]]);

	int c = 0;
	for (int i = 0; i < n; i++) {
		if (visited[i])
			continue;
		dfs(i);
		c++;
	}

	return n - c;
}

int findSwapPairs(int N, int S[], int M, int X[], int Y[], int P[], int Q[]) {
	int inplace = 0;

	int mini = N - 1;
	int s[N];
	for (int i = 0; i < N; i++)
	{
		s[i] = S[i];
		if (i == s[i])
			inplace++;
	}

	if (inplace == N)
		mini = 0;
	
	int l = 0, r = mini;
	while (l < r) {
		int mid = (r + l) / 2;
		if (mid >= numswaps(S, N, X, Y, mid))
			r = mid;
		else
			l = mid + 1;
	}

	M = min(mini, l);

	// SORTIN PHASE WHOHOOO
	int end[N];
	for (int i = 0; i < N; i++)
		end[i] = S[i];
	for (int i = 0; i < M; i++)
		swap(end[X[i]], end[Y[i]]);
	int endidx[N];
	for (int i = 0; i < N; i++)
		endidx[end[i]] = i;

	int curridx[N];
	for (int i = 0; i < N; i++)
		curridx[S[i]] = i;

	int midx = 0, swapidx = 0;
	bool should_swap = true;

	for (int i = 0; i < N; i++) {
		if (should_swap) {
			swap(S[X[midx]], S[Y[midx]]);
			swap(curridx[S[X[midx]]], curridx[S[Y[midx]]]);
			midx++;
		}

		if (end[i] == i) {
			should_swap = false;
			continue;
		}
		should_swap = true;

		int swappee = curridx[end[i]];

		P[swapidx] = curridx[i];
		Q[swapidx] = swappee;
		swapidx++;

		int prevs = S[swappee];
		swap(S[curridx[i]], S[swappee]);
		swap(curridx[i], curridx[prevs]);
		swap(end[i], end[endidx[i]]);
		swap(endidx[i], endidx[prevs]);
	}

	return M;
}


