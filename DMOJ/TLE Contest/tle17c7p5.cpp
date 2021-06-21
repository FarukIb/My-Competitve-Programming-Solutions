// this solution does not work, i worked on it all day
// i modified it and now get TLE on #40
// then after i asked my sister to code weighted bipartite matching
// she told that max flow isnt on the ioi syllabus and then i gave up
// you could probably still get some merit out of this code
// i figure it might be an infinite loop since complexity is n*n*n*logn
// idk send me an email if you see the error
// ibrahimovic.faruk@gmail.com

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

struct node
{
	int n; double weight;
	
	bool operator<(const node& b) const
	{
		return weight > b.weight;
	}
};

int cap[202][202];
vector<vector<pair<int, double> > > adj;

int sink, source, n;
map<int, int> pairs;
vector<int> parents;
bool findAugmentingPath()
{
	vector<bool> inq(n + 2, false);
	vector<double> dist(n + 2, 1e9);
	dist[source] = 0;
	
	priority_queue<node> que;
	node start; start.n = source; start.weight = 0;
	que.push(start);
	while (!que.empty())
	{
		node curr = que.top();
		que.pop();
		for (pair<int, double> i : adj[curr.n])
		{
			if (dist[i.first] > dist[curr.n] + i.second && cap[curr.n][i.first])
			{
				parents[i.first] = curr.n;
				dist[i.first] = dist[curr.n] + i.second;
				
				node toAdd; toAdd.n = i.first, toAdd.weight = dist[toAdd.n];
				que.push(toAdd);
			}
		}
	}
	if (dist[sink] == 1e9)
		return false;
	return true;
}


void fulkerson()
{
	while (findAugmentingPath())
	{
		int prev = sink, e = parents[sink];
		while (e != -1)
		{
			cap[e][prev] = 0, cap[prev][e] = 1;
			if (prev != sink && e != source)
				pairs[e] = prev;
			prev = e;
			e = parents[e];
		}
	}
}


// UTIL
double dist(pair<int, int> a, pair<int, int> b) { return sqrt((a.second - b.second) * (a.second - b.second) + (a.first - b.first) * (a.first - b.first)); }

int main()
{
	source = 0;
	
	pii arr[202];
	cin >> n;
	adj.resize(2 * n + 2);
	parents.resize(2 * n + 2, -1);
	sink = 2 * n + 1;
	
	for (int i = 1; i <= n; i++)
	{
		adj[0].push_back(pair<int, double>(i, 0.0));
		adj[i].push_back(pair<int, double>(0, 0.0));
		cap[0][i] = 1;
		cin >> arr[i].first >> arr[i].second;
	}
	
	n *= 2;
	for (int i = n / 2 + 1; i <= n; i++)
	{
		cap[i][sink] = 1;
		adj[i].push_back(pair<int, double>(sink, 0.0));
		adj[sink].push_back(pair<int, double>(i, 0.0));
		cin >> arr[i].first >> arr[i].second;
	}
	
	for (int i = 1; i <= n / 2; i++)
	{
		for (int j = n / 2 + 1; j <= n; j++)
		{
			cap[i][j] = 1;
			adj[i].push_back(pair<int, double>(j, dist(arr[i], arr[j])));
			adj[j].push_back(pair<int, double>(i, -1 * dist(arr[i], arr[j])));
		}
	}
	
	fulkerson();
	
	for (int i = 1; i <= n / 2; i++)
		cout << i << " " << pairs[i] - n / 2 << endl;
	
	return 0;
}
