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
#define ll unsigned long long

using namespace std;

ll n, mod, k, v;
ll numOff = 0, numOn = 0;

ll fastExponent(ll base, int pow)
{
	if (pow == 0)
		return 1;
	if (pow == 1)
		return base % mod;
	
	ll t = fastExponent(base, pow / 2);
	t = (t * t) % mod;
	
	if (pow % 2 == 0)
		return t;
	else
		return ((base % mod) * t) % mod;
}

ll getXOR()
{
	return fastExponent(fastExponent(2, n - 1), k) % mod;
}

ll getAND()
{
	return fastExponent(fastExponent(2, n) - 1, numOff) % mod;
}

ll getOR()
{
	return fastExponent(fastExponent(2, n) - 1, numOn) % mod;
}

int main()
{
	cin >> n >> mod >> k >> v;
	bitset<64> x(v);
	for (int i = 0; i < k; i++)
		numOn += x[i], numOff += 1 - x[i];
		
	cout << getXOR() << endl << getOR()<< endl << getAND() << endl;
	
	return 0;
}
