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

bool cmp2(int a, int b)
{
	return a > b;
}

bool cmp(pii a, pii b)
{
	return a.second > b.second;
}

int n, m, k;
int parents[(int)1e5 + 10];
int heights[(int)1e5 + 10];
bool isParent[(int)1e5 + 10];
bool visited[(int)1e5 + 10];

vector<int> values;
vector<pii> leaves;
vector<int> graph[(int)1e5 + 10];

void dfs1(int currNode, int hght)
{
	heights[currNode] = hght;
	for (int i : graph[currNode])
		if (parents[currNode] != i)
			dfs1(i, hght + 1);
}

void goUp(int currNode, int val)
{
	if (visited[currNode])
	{
		values.push_back(val);
		return;
	}
	if (currNode == 1)
	{
		visited[currNode] = true;
		values.push_back(val + 1);
		return;
	}
	visited[currNode] = true;
	goUp(parents[currNode], val + 1);
}

int friends[(int)1e5 +10];

int main()
{
	cin >> n >> m >> k;
	for (int i = 2; i <= n; i++)
	{
		cin >> parents[i];
		isParent[parents[i]] = true;
		graph[i].push_back(parents[i]);
		graph[parents[i]].push_back(i);
	}
	
	dfs1(1, 0);
	
	for (int i = 2; i <= n; i++)
		if (isParent[i] == 0)
			leaves.push_back(pii(i, heights[i]));
	sort(leaves.begin(), leaves.end(), cmp);
	
	for (pii x : leaves)
		goUp(x.first, 0);
	
	sort(values.begin(), values.end(), cmp2);
	
	while (k > values.size())
		values.push_back(0);
	
	int val = 0;
	for (int i = 0; i < m; i++)
	{
		friends[i] = values[val];
		val++;
		val %= k;
	}
	
	cout << friends[0];
	for (int i = 1; i < m; i++)
		cout << " " << friends[i];
	cout << endl;
	
	return 0;
}
