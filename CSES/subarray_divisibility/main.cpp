#include <bits/stdc++.h>
#define mp make_pair
#define all(a) a.begin(), a.end()

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;
int n;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    cin >> n;
    vector<ll> arr(n+1);
    vector<ll> cumsum(n+1);
    for (int i = 1; i <= n; i++)
    {
        cin >> arr[i];
        arr[i] %= n;
        arr[i] += n, arr[i] %= n;
        cumsum[i] = (cumsum[i - 1] + arr[i]) % n;
    }
    ll out = 0;
    map<ll, ll> cnt;
    for (int i = n; i >= 0; i--) {
        ll needed = cumsum[i];
        out += cnt[needed];
        cnt[cumsum[i]]++;
    }

    cout << out << endl;
}