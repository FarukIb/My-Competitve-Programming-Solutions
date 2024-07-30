#include <bits/stdc++.h>
#define int long long
using namespace std;

signed main()
{
    int n, c;
    cin >> n >> c;
    vector<int> a(n);
    for (int i = 0; i < n; i++)
        cin >> a[i];
    auto check = [&](int ans)
    {
        int req = 0;
        int cur = 0;
        for (int i = 0; i < n; i++)
        {
            cur += a[i];
            if (a[i] > ans)
                return false;
            if (cur > ans)
            {
                req++;
                cur = a[i];
            }
        }
        if (cur != 0)
            req++;
        if (req > c)
            return false;
        return true;
    };
    int l = 0, r = 1e9;
    while (r - l > 1)
    {
        int mid = (r + l) / 2;
        if (check(mid))
            r = mid;
        else
            l = mid;
    }
    cout << r << endl;
}
