#include <bits/stdc++.h>
#define mp make_pair
#define all(a) a.begin(), a.end()

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    ll n; cin >>n;
    cout << n << " ";
    while (n != 1) {
        if (n % 2)
            n = n *3LL + 1LL;
        else
            n /= 2;
        cout << n << " ";
    }
    cout <<endl;
}