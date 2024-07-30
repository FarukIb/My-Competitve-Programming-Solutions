#include <bits/stdc++.h>
#define pii pair<int, int>
#define ll long long
#define ld long double

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int n, q;
    cin >> n >> q;

    vector<int> arr(n + 3, 0);
    for (int i = 0; i < q; i++) {
        int l, r;
        cin >> l >> r;

        arr[l]++, arr[r + 1]--;
    }

    for (int i = 1; i <= n; i++)
        arr[i] += arr[i - 1];
    int maxi = 0;
    for (int i = 0; i <= n; i++)
        maxi = max(maxi, arr[i]);
    cout << maxi << "\n";
}
