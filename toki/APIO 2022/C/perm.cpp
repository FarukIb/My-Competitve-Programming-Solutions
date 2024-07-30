#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#include "perm.h"

std::vector<int> construct_permutation(long long k)
{
	vector<int> out;
	int b = 0, s = -1;
	bool foundOne = false;
	int last_bit = 63 - __builtin_clzll(k);
	for (int bit = last_bit - 1; bit >= 0; bit--) {
		out.push_back(b++);
		if (k & (1LL << bit))
			out.insert(out.begin(), b++);
	}

	//reverse(out.begin(), out.end());
	//for (int i = 0; i < out.size(); i++)
	//	out[i] += -(s + 1);
	
	return out;
}