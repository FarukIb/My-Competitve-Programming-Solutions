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
    ll out = 1;
    while (n--)
        out *= 2LL, out %= (ll)(1e9 + 7);
    cout << out << endl;
}