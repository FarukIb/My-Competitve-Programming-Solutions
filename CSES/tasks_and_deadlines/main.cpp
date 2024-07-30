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
    vector<pii> arr(n);
    for (int i = 0; i < n; i++)
        cin >> arr[i].first >> arr[i].second;
    sort(all(arr));
    ll sum = 0, cum_sum = 0;
    for (int i = 0; i < n; i++) {
        cum_sum += arr[i].first;
        sum += arr[i].second - cum_sum;
    }

    cout << sum << "\n";
}