#include <bits/stdc++.h>
#define mp make_pair
#define all(a) a.begin(), a.end()

using namespace std;

typedef long long ll;
typedef pair<ll, ll> pii;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    ll t;
    cin >> t;
    while (t--) {
        ll n;
        cin >> n;
        vector<ll> arr(n), prev_eq(n), nxt_eq(n); 
        for (ll i = 0; i < n; i++)
            cin >> arr[i];
        ll out = n*(n+1LL)/2; out--;
        prev_eq[0] = 0;
        for (ll i = 1; i < n; i++) {
            prev_eq[i] = i;
            if (arr[i] == arr[i - 1])
                prev_eq[i] = prev_eq[i - 1];
            out -= i - prev_eq[i] + 1;
        }  
        
        cout << out << "\n";
    }
}