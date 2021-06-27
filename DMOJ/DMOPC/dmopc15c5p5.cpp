// note: i of course, didn't get it on my own. it's a bit confusing to figure out but i eventually got it
// might start making a class for every data structure idk it looks nice
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
#define mod 1000000007

using namespace std;

class BIT
{
private:
int n;
vector<ll> tree;
public:

BIT(int size)
{
	n = size;
	tree.resize(n + 1, 0);
}

void modify(int index, ll value)
{
	while (index <= n)
		tree[index] += value, index += index & (-index);
}

ll query(int index)
{
	ll sum = 0;
	while (index > 0)
		sum += tree[index], index -= index & (-index);
	return sum;
}

};

int n, root;
vector<int> parents;
vector<int> order;
vector<ll> answer;
vector<vector<int> > adj;

void dfs(int current, BIT &bit)
{
	ll before = bit.query(order[current]);
	for (int i : adj[current])
		dfs(i, bit);
	answer[current] = (bit.query(order[current]) - before + 1) % mod;
	bit.modify(order[current], answer[current]);
}

int main()
{
	cin >> n;
	BIT bit(n + 1);
	parents.resize(n + 1);
	order.resize(n + 1);
	answer.resize(n + 1);
	adj.resize(n + 1);
	for (int i = 1; i <= n; i++)
	{
		cin >> parents[i];
		if (parents[i] == 0)
			root = i;
		else
			adj[parents[i]].push_back(i);
	}
	
	for (int i = 1; i <= n; i++)
	{
		int inp;
		cin >> inp;
		order[inp] = i;
	}
	
	dfs(root, bit);
	
	for (int i = 1; i <= n; i++)
		cout << answer[i] % mod << " ";
	cout << endl;
}
