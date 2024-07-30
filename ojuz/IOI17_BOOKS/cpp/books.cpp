#include "books.h"
#include <bits/stdc++.h>
#define mp make_pair
#define all(a) a.begin(), a.end()

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

long long minimum_walk(std::vector<int> p, int s) {
	int n = p.size();
	ll out = 0;
	vector<bool> visited(n, 0);
	int last = 0;
	for (int i = 0; i < n; i++) {
		if (visited[i] || p[i] == i)
			continue;
		out += abs(i - last);
		last = i;
		int pnt = p[i], l = i;
		visited[i] = true;
		while (pnt != i) {
			out += abs(pnt - l);
			l = pnt;
			visited[pnt] = true;
			pnt = p[pnt];
		}
		last = l;
	}
	
	out += last;
	return out;
}
