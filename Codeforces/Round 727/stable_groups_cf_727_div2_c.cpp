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

vector<ll> arr;
vector<ll> gaps;

int main()
{
	ll n, k, x;
	cin >> n >> k >> x;
	arr.resize(n);
	for (int i = 0; i < n; i++)
		cin >> arr[i];
		
	int numGaps = 0;
	sort(arr.begin(), arr.end());
	for (int i = 1; i < n; i++)
	{
		if (arr[i] - arr[i - 1] > x)
		{
			numGaps++;
			gaps.push_back(arr[i] - arr[i - 1]);
		}
	}
	
	sort(gaps.begin(), gaps.end());
	
	for (ll i : gaps)
	{
		ll need = (i - 1) / x;
		
		if (need > k)
			break;
		k -= need;
		numGaps--;
	}
	
	cout << 1 + numGaps << endl;
	
	return 0;
}
