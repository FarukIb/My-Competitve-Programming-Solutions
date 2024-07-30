#include <bits/stdc++.h>
#define mp make_pair
#define all(a) a.begin(), a.end()

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int t;
    cin >> t;
    while (t--) {
        ll x, y;
        cin >> x >>y;

        ll maxi = max(x, y);
        ll f_ele = (maxi - 1LL) * (maxi - 1LL) + 1LL;

        if (maxi % 2 == 0) {
            if (x == maxi)
                f_ele += maxi - 1LL + maxi - y;
            else    
                f_ele += x - 1;
        } else {
            if (y == maxi)
                f_ele += maxi - 1LL + maxi - x;
            else
                f_ele += y - 1;
        }
        
        cout << f_ele << endl;
    }
}