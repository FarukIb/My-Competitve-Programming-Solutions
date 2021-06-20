// visit https://hsin.hr/coci/archive/2012_2013/ for editorial :)

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

ll lcm(ll a, ll b)
{
	return a * b / __gcd(a, b);
}

ll getStrength(ll x)
{
	if (x == 2)
		return 1;
	for (ll i = 2; i <= x; i++)
		if (x % i != 0)
			return getStrength(i) + 1;
}

ll getCountUnder(ll x)
{
	ll out = 0;
	
	ll currLCM = 1;
	for (ll i = 2; currLCM <= x; i++)
	{
		ll strng = getStrength(i);
		
		out += (strng + 1) * (x / currLCM);
		currLCM = lcm(currLCM, i);
		out -= (strng + 1) * (x / currLCM);
	}
	
	return out;
}

int main()
{
	ll a, b;
	cin >> a >> b;
	
	cout << getCountUnder(b) - getCountUnder(a - 1) << endl;
	
	return 0;
}
