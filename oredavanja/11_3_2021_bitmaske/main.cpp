#include <bits/stdc++.h>
#define mp make_pair

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int n;
    cin >> n;
    vector<int> arr(n);
    for (int i = 0; i < n; i++)
        cin >>arr[i];

    int max_suma = -1e9;
    for (int mask = 0; mask < (1 << n); mask++) {
        int trenutna_suma = 0;
        for (int bit = 0; bit < n; bit++) {
            if (((1 << bit) & mask) != 0)
                trenutna_suma ^= arr[bit];
        }
        max_suma = max(max_suma, trenutna_suma);
    }

    cout << max_suma << "\n";
}