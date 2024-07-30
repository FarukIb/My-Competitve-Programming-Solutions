#include "prize.h"
#include <bits/stdc++.h>

using namespace std;

int sqrtn = 473;

vector<vector<int>> memo(2e5+1, vector<int>(2, -1));
vector<int> myask(int a) {
	if (memo[a][0] != -1)
		return memo[a];
	return memo[a]= ask(a);
}

int find_best(int n) {
	sqrtn = min(sqrtn, n);
	int max_sum = 0;
	for (int i = 0; i < sqrtn; i++)
	{
		auto a = myask(i);
		max_sum = max(max_sum, a[0] + a[1]);
		if (a[0] + a[1] == 0) {
			return i;
		}
	}

	for (int i = sqrtn; i < n; i++) {
		auto val = myask(i);
		if (val[0] + val[1] != max_sum) {
			if (val[0] + val[1] == 0)
				return i;
			continue;
		}
		
		int rval = val[1];
		int l = i, r = n - 1, ans = -1;
		while (l < r) {
			int mid = (l + r) / 2;
			auto midval = myask(mid);
			if (midval[0] + midval[1] != max_sum || midval[1] < rval)
				r = mid;
			else
				l = mid + 1, ans = mid;
		}

		i = ans;
	}

	return 0;
}
