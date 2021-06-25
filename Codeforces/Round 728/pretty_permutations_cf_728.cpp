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

int arr[101];
int main()
{
	int T;
	cin >> T;
	while (T--)
	{
		int n;
		cin >> n;
		for (int i = 1; i<= n; i++)
			arr[i] = i;
		for (int i = 1; i <= n - 1; i += 2)
			swap(arr[i], arr[i + 1]);
		
		if (n % 2 == 1)
			swap(arr[n], arr[n - 1]);
		cout << arr[1];
		for (int i = 2; i <= n; i++)
			cout << " " << arr[i];
		cout << endl;
	}
	return 0;
}
