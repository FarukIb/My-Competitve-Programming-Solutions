// i don't think this is the intended solution(i'm not sure, i didn't undestand the editorial)
// the basic logic behind it is that we seperate 3 cases
// 1: we can pick fields in a way so that their sum is equal to q
// we can check if this is the case with knapsack dp.
// if we can arrange it that way we output q
// 2: the sum of all  olive trees is bigger than q but we cant
// pick them in such a way that it is equal to q
// first, we pick some set of fields so that we their sum
// is as close to q as possible, again we can do this with knapsack dp
// we can add a random unpicked field and trim it so the total sum is equal to q
// we can always add a random trimmed tree because if we could add an untrimmed
// tree then our set previously built set was not optimal
// in this case we output q - 1
// (the number of olive trees in an untrimmed field of size x is x, 
// the number of olive trees in a strip of size x is x - 1,
// and a trimmed field is basically a strip)
// 3: the sum of all fields is lower than q
// we choose all of the fields in our set
// then we sort all the strips from biggest to smallest
// and then cram as many strips in our set

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

int cmp(ll a, ll b)
{
	return a > b;
}

vector<vector<ll> > dp;
ll q, k, m;

ll weights[4011];
ll circleSum = 0;

int main()
{
	cin >> q >> m >> k;
	
	for (int i = 1; i <= m; i++)
	{
		ll x;
		cin >> x;
		weights[i] = x;
		circleSum += x;
	}
	for (int j = 1; j <= k; j++)
	{
		ll x;
		cin >> x;
		weights[j + m] = x;
	}
	
	dp.resize(2, vector<ll>(q + 1, 0));
	
	
	// knapsack dp
	ll maxi;
	for (ll i = 1; i <= m; i++)
	{
		for (ll j = 0; j <= q; j++)
		{
			if (j >= weights[i])
				dp[1][j] = max(dp[0][j], weights[i] + dp[0][j - weights[i]]);
			else
				dp[1][j] = dp[0][j];
		}
		swap(dp[0], dp[1]);
		fill(dp[1].begin(), dp[1].end(), 0);
	}
	maxi = dp[0][q];
	ll currWght = maxi;
	
	if (currWght == q) // case 1
	{
		cout << q << endl;
		return 0;
	}
	else if (currWght < q && circleSum >= q) // case 2
	{
		cout << q - 1 << endl;
		return 0;
	}
	
	//case 3
	sort(weights + m + 1, weights + m + k + 1, cmp);
	int i = m + 1;
	while (i < m + k + 1)
	{
		if (currWght + weights[i] >= q)
		{
			ll x = q - currWght;
			maxi += max((ll)0, x - 1);
			break;
		}
		maxi += weights[i] - 1;
		currWght += weights[i];
		i++;
	}
	
	cout << maxi << endl;
	
	return 0;
}