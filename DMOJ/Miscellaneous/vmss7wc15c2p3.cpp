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

map<ll, ll> histo;
deque<ll> stac;
int n;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    ll out = 0;
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        ll x;
        cin >> x;

        while (!stac.empty() && stac.back() < x)
        {
            histo[stac.back()]--;
            out++;
            stac.pop_back();
        }
        if (!stac.empty())
        {
            if (stac.back() == x)
                out += histo[x];
            if (stac.front() != x)
                out++;
        }
        
        stac.push_back(x);
        histo[x]++;
    }

    cout << out << endl;
}