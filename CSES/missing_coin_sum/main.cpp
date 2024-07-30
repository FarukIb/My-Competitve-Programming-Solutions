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
    sort(all(arr));
    if (arr[0] != 1) {
        cout << 1 << "\n";
        return 0;
    }
    ll sum = 1;
    for (int i = 1; i < n; i++) {
        if (arr[i] > sum + 1)
            break;
        sum += arr[i];
    }
    cout << sum + 1 << "\n";
}