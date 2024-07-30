#include <bits/stdc++.h>
#define pii pair<ll, ll>
#define ll long long
#define ld long double

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int n;
    cin >> n;
    vector<ll> arr(n + 1);
    for (int i = 1; i <= n; i++)
        cin >> arr[i];
    
    vector<pii> pref(n + 1, pii(0, 0));
    for (int i = 1; i <= n; i++) {
        pref[i] = pii(arr[i], 1);
        while (pref[i].first % 2 == 0)
            pref[i].first /= 2, pref[i].second *= 2;
        pref[i].second += pref[i - 1].second;
    }

    int q;
    cin >> q;
    while (q--) {
        ll s;
        cin >> s;
        int l = 1, r = n;
        while (l < r) {
            int mid = (l + r) / 2;
            if (pref[mid].second < s)
                l = mid + 1;
            else
                r = mid;
        }

        cout << pref[l].first << "\n";
    }
}
