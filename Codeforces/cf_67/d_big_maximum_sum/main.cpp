#include <bits/stdc++.h>
#define pii pair<int, int>
#define ll long long
#define pll pair<ll, ll>
#define ld long double

using namespace std;

ll getOpt(vector<ll> arr, int n) {
    ll curr = 0;
    ll maxi = -1e18;
    for (int i = 0; i < n; i++) {
        curr += arr[i];
        if (curr < 0 || arr[i] > curr)
            curr = arr[i];
        maxi = max(maxi, curr);
    }
    return maxi;
}

pll getEnd(vector<ll> arr, int n) {
    ll curr = 0;
    pll maxi(0, 0);
    for (int i = 0; i < n; i++) {
        curr += arr[i];
        maxi = max(maxi, pll(curr, 1));
    }
    return maxi;
}

pll getBegin(vector<ll> arr, int n) {
    reverse(arr.begin(), arr.end());
    return getEnd(arr, n);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int m, n;
    cin >> m >> n;

    vector<pll> beg(m);
    vector<pll> endd(m);
    vector<ll> best(m);
    vector<ll> sum(m);
    for (int t = 0; t < m; t++) {
        int s;
        cin >> s;
        vector<ll> arr(s); ll summie = 0;
        for (int i = 0; i < s; i++)
        {
            cin >> arr[i];
            summie += arr[i];
        }
        sum[t] = summie;

        beg[t] = getBegin(arr, s);
        best[t] = getOpt(arr, s);
        endd[t] = getEnd(arr, s);
    }


    ll out = -1e18; ll curr = 0; ll siz = 0;
    for (int t = 0; t < n; t++) {
        int i;
        cin >> i;
        i--;

        out = max(out, best[i]);

        if (siz + endd[i].second > 0)
            out = max(out, curr + endd[i].first);
        curr += sum[i];
        siz++;
        if (curr < beg[i].first)
            curr = beg[i].first, siz = beg[i].second;
        if (siz > 0)
            out = max(out, curr);
    }

    cout << out << "\n";
}
