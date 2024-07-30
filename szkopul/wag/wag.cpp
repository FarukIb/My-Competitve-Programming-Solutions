#include <bits/stdc++.h>
#define mp make_pair
#define all(a) a.begin(), a.end()

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

#include "waglib.cpp"

int cmp(int a, int b) {
	poloz_lewo(a);
	poloz_prawo(b);
	int o = wazenie();
	odloz(a);
	odloz(b);
	return o;
}

int main() {
	int t = liczba_testow();
	while (t--) {
		vector<int> seq(1, 1);
		for (int i = 1; i < 7; i++) {
			int l = 0, r = i, ans = -1;
			while (l < r) {
				int mid = (l + r) / 2;
				if (cmp(i+1, seq[mid]) == 1)
					r = mid;
				else
					l = mid + 1, ans = mid;
			}
			seq.insert(seq.begin() + ans + 1, i+1);
		}
		vector<pii> stinky;
		for (int i = 0; i < 7; i++)
			stinky.push_back({seq[i], i + 1});
		sort(all(stinky));
		for (int i = 0; i < 7; i++)
			seq[i] = stinky[i].second;
		odpowiedz(seq);
	}
}
