#include <bits/stdc++.h>
#define pii pair<int, int>
#define ll long long
#define ld long double

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        int out = 0;
        for (int i = 0; i < n; i++) {
            int x;
            cin >> x;
            out |= x;
        }
        cout << out << "\n";
    }
}
