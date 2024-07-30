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
        cin >>arr[i];

    ll maxi = -1e18, c = 0;
    for (int i = 0; i < n; i++) {
        c += arr[i];
        maxi = max(maxi, c);
        c = max(c, 0LL);
    }

    cout << maxi << "\n";
}