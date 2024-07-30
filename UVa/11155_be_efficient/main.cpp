#include <bits/stdc++.h>
#define ll long long

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int T, tc = 1;
    cin >> T;
    while (T--) {
        ll a, b, c, m, n;
        cin >> a >> b >> c >> m >> n;

        a = a % m, b = b % m, c = c % m;

        map<ll, int> hist;
        hist[a]++;
        vector<ll> arr(n);
        arr[0] = a;
        for (int i = 1; i < n; i++) {
            arr[i] = arr[i - 1] * b % m;
            arr[i] += c;

            arr[i]++;
            arr[i] = arr[i] % m;

        }

        for (int i = 1; i < n; i++) {
            arr[i] += arr[i - 1];
            arr[i] = arr[i] % m;
            hist[arr[i]]++;
        }

        ll out = hist[0];
        for (int i = 0; i < n; i++) {
            hist[arr[i]]--;

            out += hist[arr[i]];
        }

        cout << "Case " << tc++ << ": " << out << "\n";
    } 
}