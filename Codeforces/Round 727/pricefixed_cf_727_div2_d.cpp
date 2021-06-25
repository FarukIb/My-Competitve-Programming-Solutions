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

#define pii pair<long long, long long>
#define ll long long

using namespace std;

int cmp(pii a, pii b)
{
	if (a.second < b.second)
		return true;
	return false;
}

vector<pii> arr;

map<ll, ll> added;
map<ll, ll> filled;
int main()
{
	int n;
	cin >> n;
	for (int i = 0; i < n; i++)
	{
		int a, b;
		cin >> a >> b;
		added[b] += a;
	}
	
	for (pii x : added)
		arr.push_back(pii(x.second, x.first));
	sort(arr.begin(), arr.end(), cmp);
	n = arr.size();
	
	ll done = 0;
	ll out = 0;
	ll r = n - 1, l = 0;
	while (l < r)
	{
		ll lef = added[arr[l].second] - filled[arr[l].second];
		//cout << added[arr[l].second] << " " << filled[arr[l].second] << " " << arr[l].second << endl;
		
		while (done < arr[l].second && l < r)
		{
			ll curr = added[arr[r].second] - filled[arr[r].second];
			if (curr <= arr[l].second - done)
				out += curr * 2, r--, done += curr;
			else
				out += (arr[l].second - done) * 2, filled[arr[r].second] += arr[l].second - done, done += arr[l].second - done;
		}
		out += lef, done += lef, l++;
	}
	
	if (l == r)
	{
		ll lef = added[arr[l].second] - filled[arr[l].second];
		if (done >= arr[l].second)
			out += lef;
		else if (done + lef <= arr[l].second)
			out += lef * 2;
		else
		{
			out += (arr[l].second - done) * 2;
			filled[arr[l].second] += arr[l].second - done;
			done += arr[l].second - done;
			
			out += arr[l].first - filled[arr[l].second];
		}
	}
	cout << out << endl;
	
	return 0;
}
