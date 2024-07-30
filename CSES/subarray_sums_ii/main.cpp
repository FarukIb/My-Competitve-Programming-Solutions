#include <bits/stdc++.h>
#define mp make_pair
#define all(a) a.begin(), a.end()

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int n; ll x;
    cin >> n >> x;
    vector<ll> arr(n + 1);
    vector<ll> cumsum(n + 1);
    set<ll> al;
    for (int i = 1; i <= n; i++) {
        cin >> arr[i];
        cumsum[i] = arr[i] + cumsum[i - 1];
        al.insert(cumsum[i]);
        al.insert(0);
        al.insert(1e18);
    }

    map<ll, int> cnt;
    ll out = 0;
    for (int i = n; i >= 0; i--) {
        // x = cumsum[O] - cumsum[i];
        ll needed = cumsum[i] + x;
        out += cnt[needed];
        cnt[cumsum[i]]++;
    }

    cout << out << endl;
}