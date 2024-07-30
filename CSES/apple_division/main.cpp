#include <bits/stdc++.h>
#define mp make_pair
#define all(a) a.begin(), a.end()

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int n;
    cin >> n;
    vector<ll> arr(n);
    for (int i = 0; i < n; i++)
        cin >> arr[i];
    ll sum = accumulate(all(arr), 0LL); ll out = sum;
    for (int mask = 0; mask < (1 << n); mask++) {
        ll m = 0;
        for (int i = 0; i < n; i++)
            if (((1 << i) & mask) != 0)
                m += arr[i];
        out = min(out, abs(2LL * m - sum));
    }

    cout << out << "\n";
}