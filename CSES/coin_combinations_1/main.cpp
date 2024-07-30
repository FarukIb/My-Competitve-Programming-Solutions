#include <bits/stdc++.h>
#define mp make_pair

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

const ll mod = 1e9 + 7;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int n, x;
    cin >> n >> x;
    vector<int> arr(n);
    for (int i = 0; i < n; i++)
        cin >> arr[i];
    vector<ll> numways(x + 1, 0);
    numways[0] = 1;

    for (int i = 0; i < n; i++) {
        for (int j = arr[i]; j <= x; j++)
            numways[j] += numways[j - arr[i]], numways[j] %= mod;
    }

    cout << numways[x] << "\n";
}