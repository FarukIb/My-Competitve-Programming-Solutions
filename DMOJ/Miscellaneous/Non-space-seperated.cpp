// we use bitmask brute force here
// a bit at the i-th place represents a split between the i-th and i+1-th digit
// since there are at most 12 possible splits the complexity is at most 2 to the 12
// which is more than sufficient

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

map<ll, int> sums;
string s;
string arr[101];

void processMask(int mask)
{
	bitset<13> msk(mask);
	
	ll sum = 0;
	string currS = ""; currS += s[0]; 
	for (int i = 0; i < s.size() - 1; i++)
	{
		if (msk[i])
		{
			sum += stoll(currS, nullptr, 10);
			currS = "";
		}
		currS += s[i + 1];
	}
	sum += stoll(currS, nullptr, 10);
	
	sums[sum]++;
}

int main()
{
	cin >> s;
	
	for (int i = 0; i < 1 << (s.size() - 1); i++)
		processMask(i);
	
	ll possible = 0;
	ll sum = (ll)1e14, app = 0;
	for (pii i : sums)
	{
		possible++;
		if (i.second > app)
			sum = i.first, app = i.second;
		else if (i.second == app && i.first < app)
			sum = i.first;
	}
	
	cout << possible << sum << endl;
	
	return 0;
}
