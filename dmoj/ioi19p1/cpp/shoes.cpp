#include "shoes.h"
#include <bits/stdc++.h>
#define mp make_pair
#define all(a) a.begin(), a.end()

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

struct seggy {
	int n;
	vector<ll> t;

	seggy(ll siz) {n = siz, t.resize(2*n);}

	ll query(int l, int r) {
		ll out = 0;
		for (l += n, r += n+1; l < r; l /= 2, r /= 2) {
			if (l & 1)
				out += t[l++];
			if (r & 1)
				out += t[--r];
		}
		return out;
	}

	void upd(int idx, int val) {
		idx += n;
		while (idx > 0)
			t[idx] += val, idx /= 2;
	}
};

ll count_inv(vector<int> perm) {
	seggy seg(perm.size());
	ll out = 0;
	for (int i = 0; i < perm.size(); i++) {
		out += seg.query(perm[i], perm.size() - 1);
		seg.upd(perm[i], 1);
	}
	return out;
}

void transform(vector<int> &s) {
	set<ll> not_taken;
	for (int i = 0; i < s.size()/2; i++)
		not_taken.insert(i+1);
	for (int i : s)
		not_taken.erase(abs(i));
	
	vector<vector<ll> > new_vals(s.size()/2+1);
	for (int i = 0; i < s.size(); i++) {
		if (s[i] > 0) {
			if (new_vals[s[i]].empty())
				new_vals[s[i]].push_back(s[i]);
			else
				new_vals[s[i]].push_back(*not_taken.begin()), s[i] = *not_taken.begin(), not_taken.erase(not_taken.begin());
		}
	}
	vector<ll> pnts(s.size()/2+1);
	for (int i = 0; i < s.size(); i++) {
		if (s[i] < 0)
			s[i] = -new_vals[-s[i]][pnts[-s[i]]++];
	}
}

long long count_swaps(std::vector<int> s) {
	ll n = s.size();
	transform(s);

	vector<int> order(n/2+1, -1);
	int pnt = 0;
	for (int i = 0; i < s.size(); i++) {
		if (order[abs(s[i])] != -1)
			continue;
		order[abs(s[i])] = pnt++;
	}

	vector<int> neww(n);
	for (int i = 0; i < s.size(); i++) {
		neww[i] = order[abs(s[i])]*2;
		if (s[i] > 0)
			neww[i]++;
	}

	return count_inv(neww);
}
