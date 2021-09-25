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
#include <set>

#define pii pair<int, int>
#define ll long long

using namespace std;

struct point
{
    int x, y;
    point() { x = 0, y = 0; }
    point(int _x, int _y) { x = _x, y = _y; }
};

struct line
{
    ll y1, y2, x;
    line() { y1 = 0, y2 = 0; }
    line (ll _y1, ll _y2, ll _x) { y1 = _y1, y2 = _y2, x = _x; }

    bool operator<(const line& b) const { return x < b.x; }
};

struct query
{
    line lin;
    ll val;

    query() { val = 0, lin = line(); }
    query(ll _val, line _lin) { val = _val, lin = _lin; }

    bool operator<(const query& b) const { return lin < b.lin; }
};

int n;
ll t;

map<ll, ll> keys; // key = x value, value = index in line(from i - 1 to i)
ll lineVal[5000];

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    set<ll> Ys;
    set<ll> Xs;
    vector<query> queries;
    cin >> n >> t;
    for (int i = 0; i < n; i++)
    {
        ll tint;
        point a, b;
        cin >> a.x >> a.y >> b.x >> b.y >> tint;
        line l1(a.y, b.y, a.x), l2(a.y, b.y, b.x);
        Ys.insert(a.y);
        Ys.insert(b.y);
        Xs.insert(a.x);
        Xs.insert(a.x);

        query aa(tint, l1), bb(-tint, l2);
        queries.push_back(aa);
        queries.push_back(bb);
    }
    sort(queries.begin(), queries.end());
    
    vector<ll> sortedXs;
    vector<ll> sortedYs;
    for (ll x : Ys)
        sortedYs.push_back(x);
    sort(sortedYs.begin(), sortedYs.end());

    for (ll y : Xs)
        sortedXs.push_back(y);
    sort(sortedXs.begin(), sortedXs.end());
    
    for (int i = 0; i < sortedYs.size(); i++)
        keys[sortedYs[i]] = i;

    ll out = 0, ind = 0;
    for (int qq = 0; qq < queries.size();)
    {
        query q = queries[qq];
        ind++;

        for (int i = keys[q.lin.y1] + 1;  i <= keys[q.lin.y2]; i++)
            lineVal[i] += q.val;
        for (int i = 0; i < Ys.size(); i++)
        {
            if (lineVal[i] >= t)
                out += ((sortedYs[i] - sortedYs[i - 1]) + 1) * ;
        }
    }

    cout << out << endl;
}