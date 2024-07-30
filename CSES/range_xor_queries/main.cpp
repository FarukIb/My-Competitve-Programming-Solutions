#include <bits/stdc++.h>
#define mp make_pair
#define all(a) a.begin(), a.end()

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int n, q;
    cin >> n >> q;
    vector<int> arr(n + 1);
    for (int i = 1; i <= n; i++)
    {
        cin >> arr[i];
        arr[i] ^= arr[i - 1];
    }
    while (q--) {
        int l, r;
        cin >> l >> r;
        cout << (arr[r] ^ arr[l - 1]) << "\n";
    }
}