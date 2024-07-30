#include <bits/stdc++.h>
#define all(a) a.begin(), a.end()
#define mp make_pair

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int t;
    cin >> t;
    while (t--)
    {
        ll a, b;
        cin >> a >> b;

        ll x = (2 * b - a) / 3;
        ll y = b - x * 2;
        if (x < 0 || y < 0 || (x + y*2 != a) || (x*2 + y != b))
            cout << "NO\n";
        else
            cout << "YES\n";
    }
    
}