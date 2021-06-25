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

ll arr[(int)1e5];
int contribution[(int)1e5];
int main()
{
	int T, n;
	cin >> T;
	while (T--)
	{
		cin >> n;
		ll curr = 0;
		for (int i = 0; i < n; i++)
			cin >> arr[i];
		
		ll currSum = 0;
		sort(arr, arr + n);
		for (int i = 1; i < n; i++)
		{
			curr += arr[i] - arr[i - 1];
			curr -= arr[i] * i - currSum;
			currSum += arr[i];
		}
		cout << curr << endl;
	}
	return 0;
}
