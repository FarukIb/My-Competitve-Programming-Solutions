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
int main()
{
	int T;
	cin >> T;
	while (T--)
	{
		int n, cnt = 0;
		cin >> n;
		for (int i = 0; i < n; i++)
		{
			cin >> arr[i];
			for (int j = i - ((2 * (i + 1)) % arr[i]); j >= 0; j-= arr[i])
				if (i + j + 2 == arr[i] * arr[j] && j < i)
					cnt++;
		}
		cout << cnt << endl;
	}
	return 0;
}
