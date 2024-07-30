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
    ll sum = n *(n + 1) / 2;
    n--;
    while (n--) {
        ll inp;
        cin >>inp;
        sum -= inp;
    }
    cout << sum << endl;
}