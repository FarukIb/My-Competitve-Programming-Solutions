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

long double cumSum[(int)4e5];
long double arr[(int)4e5];

using namespace std;

int n, k;

bool works(long double p)
{
	cumSum[0] = arr[0] - p;
	for (int i = 1; i < n; i++)
		cumSum[i] = cumSum[i - 1] + arr[i] - p;
	
	long double mini = 0;
	for (int i = k - 1; i < n; i++)
	{
		if (cumSum[i] >= mini)
			return true;
		mini = min(cumSum[i - k + 1], mini);
	}
	
	return false;
}

long double binSearch()
{
	long double l = 0, r = 2e6;
	while (r - l > 1e-6)
	{
		if (works((r + l) / 2))
			l = (r + l) / 2;
		else
			r = (r + l) / 2;
	}
	return l;
}

int main()
{
	cin >> n >> k;
	for (int i = 0; i < n; i++)
		cin >> arr[i];
	
	cout << fixed << setprecision(6) << binSearch() << endl;
	return 0;
}
