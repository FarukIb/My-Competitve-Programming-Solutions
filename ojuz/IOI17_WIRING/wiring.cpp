#include "wiring.h"
#include <bits/stdc++.h>
#define mp make_pair
#define all(a) a.begin(), a.end()

using namespace std;

typedef long long ll;
typedef pair<ll, ll> pii;

vector<ll> r, b;
vector<pii> arr;

ll dist_to_nearest(ll idx) {
	vector<ll> *my;
	if (arr[idx].second == 1)
		my = &b;
	else
		my = &r;
	
	auto pnt = lower_bound(my->begin(), my->end(), arr[idx].first);
	if (pnt == my->end())
		return abs(arr[idx].first - *prev(pnt));
	else if (pnt == my->begin())
		return abs(*pnt - arr[idx].first);
	else
		return min(abs(*pnt - arr[idx].first), abs(arr[idx].first - *prev(pnt)));
}

long long min_total_length(std::vector<int> a, std::vector<int> c) {
	int n = a.size() + c.size();
	arr.push_back({-1, 0});
	for (int x : a) {
		r.push_back(x);
		arr.push_back(pii(x, 1));
	}
	for (int y : c) {
		b.push_back(y);
		arr.push_back(pii(y, -1));
	}
	sort(all(arr));
	vector<int> memo(2*n+1, -1);
	vector<int> lastt(n+1, -1);
	int balance = n;
	memo[n] = 0;
	
	vector<ll> sumr(n+1), sumb(n+1);
	for (int i = 1; i <= n; i++) {
		sumr[i] = sumr[i - 1], sumb[i] = sumb[i - 1];
		if (arr[i].second == 1) {
			sumr[i] += arr[i].first;
			balance++;
		} else {
			sumb[i] += arr[i].first;
			balance--;
		}
		lastt[i] = memo[balance];
		memo[balance] = i;
	}

	vector<ll> dp(n+1);
	for (int i = 1; i <= n; i++) {
		dp[i] = dp[i - 1] + dist_to_nearest(i);
		if (lastt[i] != -1)
			dp[i] = min(dp[i], dp[lastt[i]] + abs((sumr[i] - sumr[lastt[i]]) - (sumb[i] - sumb[lastt[i]])));
	}

	return dp[n];
}
