#include <bits/stdc++.h>
#define pii pair<int, int>
#define ll long long
#define ld long double

using namespace std;

//vector<ll> msum;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    ll min1 = 1e18, min2 = 1e18;
    int n;
    cin >> n;
    ll curr = 0, last = 0;
    for (int i = 0; i < n; i++)
    {
        ll s;
        cin >> s;
        if (i % 2)
            curr -= 2 * s;
        else
            curr += 2 * s;
        if (i % 2)
            min2 = min(-curr - last, min2);
        else
            min1 = min(curr - last, min1);
        if (i % 2)
            last = -curr;
        else
            last = curr;
    }
    //for (ll x : msum)
      //  cout << x << "\n";

    cout << max(0LL, min2 / 2 + min1 / 2 + 1) << "\n";
}