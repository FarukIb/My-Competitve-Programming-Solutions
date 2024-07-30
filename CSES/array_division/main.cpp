#include <bits/stdc++.h>
#define mp make_pair
#define all(a) a.begin(), a.end()

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

int n, k;
vector<ll> arr;
bool possible(ll max_sum) {
    ll curr = 0;
    if (*max_element(all(arr)) > max_sum)
        return false;
    ll cnt = 1; ll csum = 0;
    for (int i = 0; i < n; i++) {
        if (csum + arr[i] > max_sum)
            csum = 0, cnt++;
        csum += arr[i];
    }
    return cnt <= k;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    cin >> n >> k;
    arr.resize(n);
    for (int i = 0; i < n; i++)
        cin >> arr[i];
    ll l = 0, r = 1e18, ans =0;
    while (l < r) {
        ll mid = (l + r) / 2;
        if (!possible(mid))
            l = mid + 1;
        else
            r = mid, ans = mid;
    }

    cout << ans << endl;
}