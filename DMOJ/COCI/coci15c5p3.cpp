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
#define MOD (int)1e9 + 7

using namespace std;

ll mat[55][100010];
ll arr[100010], n, k;
int main()
{
	cin >> n >> k;
	for (int i = 0; i < n; i++)
		cin >> arr[i];
	sort(arr, arr + n);
	
	for (int i = 0; i < n; i++)
		mat[1][i] = 1;
	
	for (int i = 2; i <= k; i++)
	{
		for (int j = i - 1; j < n; j++)
			mat[i][j] = mat[i][j - 1] + mat[i - 1][j - 1], mat[i][j] %= MOD;
	}
	
	ll out = 0;
	for (int i = 0; i < n; i++)
		out += mat[k][i] * arr[i], out %= MOD;
		
	cout << out << endl;
	
	return 0;
}
