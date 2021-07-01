//NOTE: fast I/O is very importont if not neccessary for this task

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
typedef long long ll;

using namespace std;

struct coordinates
{
	ll x, y;
};

coordinates infection;

ll getDist(coordinates a, coordinates b)
{
	ll dist = (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
	return dist;
}

bool done[3011];
ll dist[3011];
ll adjMat[3011][3011], n, q, infectionIndex;
coordinates cities[3011];

int i, j;
void dijkstra(int start)
{
	for (i = 0; i <= n; i++)
		dist[i] = (ll)1e17;
	dist[start] = 0;
	
	for (i = 1; i <= n; i++)
	{
		int v = -1;
		for (j = 1; j <= n; j++)
			if (!done[j] && (v == -1 || dist[v] > dist[j]))
				 v = j;
		done[v] = true;
		
		for (j = 1; j <= n; j++)
			if (dist[j] > dist[v] + adjMat[v][j])
				dist[j] = dist[v] + adjMat[v][j];
	}
	
}

int binarySearch(ll x)
{
	int l = 0, r = n + 1;
	while (l < r)
	{
		int mid = (l + r) / 2;
		if (dist[mid] > x)
			r = mid;
		else
			l = mid + 1;
	}
	return l;
}

int main()
{
	ios_base::sync_with_stdio(false);
    cin.tie(NULL);
	
	cin >> n;
	for (i = 1; i <= n; i++)
		cin >> cities[i].x >> cities[i].y;
	
	for (i = 1; i <= n; i++)
		for (j = 1; j <= n; j++)
			adjMat[i][j] = getDist(cities[i], cities[j]);
	cin >> infectionIndex >> q;
	
	dijkstra(infectionIndex);
	sort(dist, dist + n + 1);
	
	for (i = 0; i < q; i++)
	{
		ll inp;
		cin >> inp;
		int index = binarySearch(inp);
		if (dist[index] > inp)
			index--;
		cout << index + 1 << endl;
	}
	
	return 0;
}
