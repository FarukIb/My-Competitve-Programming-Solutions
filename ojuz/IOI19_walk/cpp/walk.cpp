#include "walk.h"
#include <bits/stdc++.h>
#define mp make_pair
#define all(a) a.begin(), a.end()

using namespace std;

typedef long long ll;
typedef pair<ll, ll> pii;

vector<vector<pii> > graph;
vector<map<ll, ll> > idxs; // for each i , idxs[i][a] is index of node at that llersection
vector<ll> x;
ll n;

ll get_idx_at_height(ll a, ll h) {
	ll my_node = idxs[a][h];
	if (my_node == 0)
	{
		my_node = graph.size(), idxs[a][h] = my_node;
		graph.push_back(vector<pii>());
	}
	return my_node;
}

void add_edge(ll a, vector<ll> nei, ll h) {
	ll my_node = get_idx_at_height(a, h);
	for (ll b : nei) {
		ll idx = get_idx_at_height(b, h);
		graph[idx].push_back(mp((ll)my_node, (ll)abs(x[a] - x[b])));
		graph[my_node].push_back(mp((ll)idx, (ll)abs(x[a] - x[b])));
	}
}

struct bridge {
	ll l, r, h;
	bridge() {}
	bridge(ll L, ll R,ll H) {l = L, r = R, h = H;}
};

bool cmp(bridge a, bridge b) {return a.h > b.h;}

struct tower {
	ll idx, h, x;
	tower() {}
	tower(ll L,ll H, ll X) {idx = L, h = H, x=X;}
};

bool cmp2(tower a, tower b) {return a.h > b.h;}

ll dijkstra(ll a, ll b) {
	priority_queue<pii, vector<pii>, greater<pii>> q;
	q.push({0, a});
	vector<ll> dist(graph.size(), 1e18);
	dist[a] = 0;
	while (!q.empty()) {
		pii curr = q.top(); q.pop();
		if (curr.first > dist[curr.second])
			continue;
		for (pii O : graph[curr.second]) {
			ll t = O.first;
			ll w = O.second;
			if (dist[t] > curr.first + w) {
				dist[t] = curr.first + w;
				q.push({dist[t], t});
			}
		}
	}
	if (dist[b] == 1e18)
		return -1;
	return dist[b];
}

long long min_distance(std::vector<int> x, std::vector<int> h, std::vector<int> l, std::vector<int> r, std::vector<int> y, int s, int g) {
	::x = vector<ll>(x.begin(), x.end());
	n = x.size();
	graph.resize(n);
	idxs.resize(n);
	vector<tower> towersort(n);
	for (ll i = 0; i < n; i++)
	 	towersort[i] = tower(i, h[i], x[i]);
	sort(all(towersort), cmp2);
	ll m = l.size();
	vector<bridge> bridges(m);
	for (ll i = 0; i < m; i++)
		bridges[i] = bridge(l[i], r[i], y[i]);
	sort(all(bridges), cmp);

	ll pnt = 0;
	set<ll> xs;
	for (auto bridge : bridges) {
		while (pnt < n and towersort[pnt].h >= bridge.h)
			xs.insert(towersort[pnt++].idx);
		auto lowest = xs.lower_bound(bridge.l);
		auto highest = xs.upper_bound(bridge.r);
		auto prev = lowest;
		for (; lowest != highest; lowest = next(lowest)) {
			vector<ll> nei;
			if (prev != lowest)
				nei.push_back(*prev);
			if (next(lowest) != highest)
				nei.push_back(*next(lowest));
			
			add_edge(*lowest, nei, bridge.h);
			prev = lowest;
		}
	}

	for (ll i = 0; i < n; i++) {
		map<ll, ll> hghts = idxs[i];
		pii prev = {0, i};
		for (pii a : hghts) {
			graph[prev.second].push_back(mp(a.second, abs(a.first - prev.first)));
			graph[a.second].push_back(mp(prev.second, abs(a.first - prev.first)));
			prev = a;
		}
	}

	return dijkstra(s, g);
}
