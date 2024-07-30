#include <bits/stdc++.h>
#define mp make_pair
#define all(a) a.begin(), a.end()

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    ll n;
    cin >> n;
    for (ll i = 1; i <= n; i++) {
        cout << (i - 1LL) * (i + 4LL) * (i * i - 3LL*i + 4LL)/2LL << endl;
    }
}