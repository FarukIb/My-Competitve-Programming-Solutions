#include <bits/stdc++.h>
#define mp make_pair
 
using namespace std;
 
typedef long long ll;
typedef pair<ll, ll> pii;
 
const ll INF = 1e15;
 
ll maxi[(int)2e5];
 
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
 
    ll n, q;
    cin >> n >> q;
    vector<pii> arr(n);
    for (ll i = 0; i < n; i++)
        cin >> arr[i].first;
    for (ll i = 0; i < n; i++)
        cin >> arr[i].second;
    while (q--) {
        ll a, b;
        cin >> a >> b;
 
        maxi[0] = 0;
        for (int i = 1; i <= n + 10; i++)
            maxi[i] = -INF;
        int first = 0, second = 1;
        for (ll i = 0; i < n; i++) {
            ll c = arr[i].second, val = arr[i].first;
 
            ll same_col = maxi[c] + val * a;
            if (maxi[c] == -INF)
                same_col = -INF;
            ll dif_col;
            if (first == c)
                dif_col = maxi[second] + val * b;
            else
                dif_col = maxi[first] + val * b;
            
            if (maxi[c] < max(same_col, dif_col))
            {
                ll val = max(same_col, dif_col);
                if (val > maxi[first]) {
                    if (first != c) {
                        second = first;
                        first = c;
                    }
                    else {
                        first = c;
                    }
                }
                else if (val > maxi[second] && c != first)
                    second = c;
                maxi[c] = val;
            }
        }
        ll maxval = 0;
        for (int i = 0; i <= n; i++)
            maxval = max(maxval, maxi[i]);
        cout << maxval << "\n";
    }
}