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

int dp[1000][1000], n;
string s;

int solve(int l, int r)
{
	if (l > r)
		return 0;
	if (dp[l][r] != -1)
		return dp[l][r];
	
	if (s[l] == s[r])
		dp[l][r] = solve(l + 1, r - 1);
	else
		dp[l][r] = 1 + min(solve(l + 1, r), solve(l, r - 1));
	return dp[l][r];
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	
	for (int p = 0; p < 5; p++)
	{
		cin >> s;
		n = s.size();
		
		for (int i = 0; i < n; i++)
			for (int j = i; j < n; j++)
				dp[i][j] = -1;
		
		cout << n - solve(0, n - 1) << endl;
	}
	
	return 0;
}
