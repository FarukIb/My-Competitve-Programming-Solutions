#include "werewolf.h"
#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> pii;

const int K = 20;

struct rmaxq {
	int n;
	vector<vector<int> > table;
	vector<int> lg;
	rmaxq(vector<int> arr) {
		n = arr.size();
		lg.resize(n + 1);
		for (int i = 2; i < n; i++)
			lg[i] = lg[i / 2] + 1;
		table.resize(K, vector<int>(n));
		table[0] = arr;

		for (int i = 1; i < K; i++)
			for (int j = 0; j + (1 << i) <= n; j++)
				table[i][j] = max(table[i - 1][j], table[i - 1][j + (1 << (i - 1))]);
	}

	int query(int l, int r) {
		int o = lg[r - l + 1];
		return max(table[o][l], table[o][r - (1 << o) + 1]);
	}
};

struct rminq {
	int n;
	vector<vector<int> > table;
	vector<int> lg;
	rminq(vector<int> arr) {
		n = arr.size();
		lg.resize(n + 1);
		for (int i = 2; i < n; i++)
			lg[i] = lg[i / 2] + 1;
		table.resize(K, vector<int>(n));
		table[0] = arr;

		for (int i = 1; i < K; i++)
			for (int j = 0; j + (1 << i) <= n; j++)
				table[i][j] = min(table[i - 1][j], table[i - 1][j + (1 << (i - 1))]);
	}

	int query(int l, int r) {
		int o = lg[r - l + 1];
		return min(table[o][l], table[o][r - (1 << o) + 1]);
	}
};

vector<vector<int> > graph;

int n;
vector<int> curr1;
vector<int> curr2;
void dfs(int curr, int par, int cnt) {
	int C = 0;
	if (cnt == 0)
		curr1.push_back(curr);
	else
		curr2.push_back(curr);

	for (int a : graph[curr]) {
		if (a != par) {
			if (cnt != 0)
				dfs(a, par, cnt);
			else
				dfs(a, par, ++C);
		}
	}
}

vector<int> get_arr() {
	dfs(0, -1, 0);
	reverse(curr2.begin(), curr2.end());

	for (int a : curr2)
		curr1.push_back(a);
	return curr1;
}

std::vector<int> check_validity(int N, std::vector<int> X, std::vector<int> Y,
                                std::vector<int> S, std::vector<int> E,
                                std::vector<int> L, std::vector<int> R) {
	int Q = S.size();
	vector<int> A(Q);
	n = N;
	graph.resize(n);
	for (int i = 0; i < X.size(); i++) {
		graph[X[i]].push_back(Y[i]);
		graph[Y[i]].push_back(X[i]);
	}
	vector<int> arr = get_arr();
	vector<int> pos(n);
	for (int i = 0; i < n; i++)
		pos[arr[i]] = i;
	
	rmaxq maxi(arr);
	rminq mini(arr);

	for (int i = 0; i < Q; i++) {
		int f = S[i], s = E[i];

		if (f < L[i] || s > R[i])
			continue;
		vector<pii> intervals;
		if (f < s) {
			int l = f, r = n - 1, ans = n - 1;
			while (l < r) {
				int mid = (l + r) / 2;
				int value = mini.query(f, mid);
				if (value < L[i])
					r = mid;
				else
					ans = l, l = mid + 1;
			}
			intervals.push_back({f, ans});

			l = s, r = 0, ans = 0;
			while (l < r) {
				int mid = (l + r) / 2;
				int value = maxi.query(mid, s);
				if (value > R[i])
					r = mid;
				else
					l = mid + 1, ans = l;
			}
		}
	}

	return A;
}
