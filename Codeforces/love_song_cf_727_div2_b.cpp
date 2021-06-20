#include <algorithm>
#include <iostream>
#include <cstring>
#include <iomanip>
#include <bitset>
#include <math.h>
#include <string>
#include <vector>
#include <cmath>
#include <queue>
#include <stack>
#include <map>

#define pii pair<int, int>
#define ll long long

using namespace std;

int n, q;

vector<vector<int> > cumSum;
string arr;

vector<int> add(vector<int> a, vector<int> b)
{
	for (int i = (int)'a'; i <= (int)'z'; i++)
		a[i] += b[i];
	return a;
}

vector<int> substract(vector<int> a, vector<int> b)
{
	for (int i = (int)'a'; i <= (int)'z'; i++)
		a[i] -= b[i];
	return a;
}

int cmp(pair<char, int> a, pair<char, int> b)
{
	if (a.second < b.second)
		return true;
	return false;
}

int main()
{
	cin >> n >> q;
	vector<int> empt((int)'z' + 1, 0);
	cumSum.resize(n + 1, empt);
	cin >> arr;
	
	for (int i = 0; i < n; i++)
		cumSum[i][(int)arr[i]]++;
	for (int i = 1; i < n; i++)
		cumSum[i] = add(cumSum[i], cumSum[i - 1]);
		
	for (int t = 0; t < q; t++)
	{
		vector<int> order((int)'z' + 1);
		
		int l, r;
		cin >> l >> r;
		l--, r--;
		
		vector<int> curr;
		if (l == 0)
			curr = cumSum[r];
		else
			curr = substract(cumSum[r], cumSum[l - 1]);
		
		ll out = 0;
		for (int i = (int)'a'; i <= (int)'z'; i++)
			out += curr[i] * (i + 1 - 'a');
			
		cout << out << endl;
	}
	
	return 0;
}
