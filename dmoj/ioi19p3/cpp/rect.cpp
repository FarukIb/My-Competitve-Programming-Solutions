#include "rect.h"
#include <bits/stdc++.h>
#define mp make_pair
#define all(a) a.begin(), a.end()

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

int cumsum(int l, int r, vector<int>& a) {
	return a[r] - a[l - 1];
}
vector<vector<vector<int> > > colsum;
vector<vector<vector<int> > > rowsum;

bool good(int i, int j, int k, int l) { return (cumsum(k, l, colsum[i][j]) == 0 and cumsum(i, j, rowsum[k][l]) == 0); }

int n, m;
long long count_rectangles(std::vector<std::vector<int> > a) {
	n = a.size(), m = a[0].size();
	vector<pair<pii, pii> > points;
	colsum = vector<vector<vector<int> > >(n, vector<vector<int> >(n, vector<int>(m)));
	for (int l = 1; l < n - 1; l++) {
		for (int r = l; r < n - 1; r++) {
			for (int i = 1; i < m - 1; i++) {
				int ok = 0;
				for (int j = l; j <= r; j++) {
					if (a[j][i] >= a[l - 1][i] || a[j][i] >= a[r + 1][i])
						ok = 1;
				}
				if (!ok) {
					points.push_back(mp(mp(l, i), mp(r, i)));
				}
				colsum[l][r][i] += ok + colsum[l][r][i - 1];
			}
		}
	}
	rowsum = vector<vector<vector<int> > >(m, vector<vector<int> >(m, vector<int>(n)));
	for (int l = 1; l < m - 1; l++) {
		for (int r = l; r < m - 1; r++) {
			for (int i = 1; i < n - 1; i++) {
				int ok = 0;
				for (int j = l; j <= r; j++) 
					if (a[i][j] >= a[i][l - 1] || a[i][j] >= a[i][r + 1])
						ok = 1;
				rowsum[l][r][i] += ok + rowsum[l][r][i - 1];
			}
		}
	}

	int cnt = 0;
	for (auto corn : points) {
		int y = corn.first.second;
		int lowx = corn.second.first, highx = corn.first.first;
		for (int i = 1; i <= y; i++)
			if (good(lowx, highx, i, y))
				cnt++;
	}

	return cnt;
}