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

int n, siz = 0;
vector<int> arr;
vector<vector<int> > out;

bool visited[101];
vector<int> path;
void dfs(int x, int start)
{
	visited[x] = true;
	path.push_back(x);
	if (x == start)
		return;
	dfs(arr[x], start);
}

int main()
{
	cin >> n;
	arr.resize(n + 1);
	for (int i = 1; i <= n; i++)
		cin >> arr[i];
		
	for (int i = 1; i <= n; i++)
	{
		if (visited[i])
			continue;
		path.clear();
		dfs(arr[i], i);
		if (path.size() == 1)
			continue;
		out.push_back(path);
		siz += path.size();
	}
	
	if (out.size() < 2)
	{
		cout << out.size() << endl;
		for (vector<int> x : out)
		{
			cout << x.size();
			for (int i : x)
				cout << " " <<  i;
			cout << endl;
		}
	}
	else
	{
		cout << 2 << endl;
		cout << siz;
		for (vector<int> out : out)
			for (int i : out)
				cout << " " <<  i;
			
		cout << endl << out.size();
		for (int i = out.size() - 1; i >= 0; i--)
			cout << " " << out[i][0];
		cout << endl;
	}
	
	
	
	return 0;
}
