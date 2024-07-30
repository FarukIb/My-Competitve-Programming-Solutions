#include "vision.h"
#include <bits/stdc++.h>
#define mp make_pair
#define all(a) a.begin(), a.end()

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

int h, w;
int getidx(int i, int j) {return i*w+j;}

void construct_network(int H, int W, int K) {
	h = H, w = W;
	vector<int> fin;
	for (int i = 0; i < h; i++) {
		for (int j = 0; j < w; j++) {
			vector<int> dist;
			if ((i + j != 0 and (H*W*3 + 1) > 10000))
				continue;
			for (int k = 0; k < h; k++) 
				for (int l = 0; l < w; l++)
					if (abs(i - k) + abs(j - l) == K)
						dist.push_back(getidx(k, l));
			if (dist.empty())
				continue;
			int one = add_xor(dist);
			int two = add_or(vector<int>({getidx(i, j)}));
			fin.push_back(add_and(vector<int>({one, two})));
		}
	}
	if (fin.empty())
	{
		int a = add_not(0), b = add_not(a);
		add_and(vector<int>({a, b}));
	}
	else
		add_or(fin);
}
 