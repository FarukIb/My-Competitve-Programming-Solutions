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
#define MOD (int)1e9 + 7

using namespace std;

int n;
ll l, b;
vector<ll> cumSum;

ll getSum(int l, int r) { return cumSum[r] - cumSum[l - 1]; }
ll getWeightOfSegment(ll l, ll r)
{

    ll median = 0.0;
    if ((l + r) % 2 == 0)
        median = getSum((l + r) / 2, (l + r) / 2);
    else
        median = getSum((l + r) / 2, (l + r) / 2 + 1) / 2;

    ll left, right;
    if ((l + r) % 2 == 0)
        left = getSum(l, (l + r) / 2 - 1), right = getSum((l + r) / 2 + 1, r);
    else
        left = getSum(l, (l + r) / 2), right = getSum((l + r) / 2 + 1, r);

    ll out = 0;
    if ((l + r) % 2 == 0)
        out += median * ((l + r) / 2 - l) - left, out += right - median * (r - (l + r) / 2);
    else
        out += median * ((l + r) / 2 - l + 1) - left, out += right - median * (r - (l + r) / 2);

    return out;
}

ll getMinSegment(ll len)
{
    len--;
    ll mini = (ll)1e17;
    for (int i = 1; i <= n - len; i++)
        mini = min(mini, getWeightOfSegment(i, i + len));
    return mini;
}

int binary_search()
{
    int l = 0, r = n;
    while (l < r)
    {
        int mid = (l + r) / 2;
        ll minSeg = getMinSegment(mid);
        if (minSeg > b)
            r = mid;
        else
            l = mid + 1;
    }
    return l - 1;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> l >> b;
    cumSum.resize(n + 1);
    cumSum[0] = 0;

    for (int i = 1; i <= n; i++)
    {
        cin >> cumSum[i];
        cumSum[i] += cumSum[i - 1];
    }

    if (getWeightOfSegment(1, n) <= b)
        cout << n << endl;
    else
        cout << binary_search() << endl;
}
