#include <bits/stdc++.h>
#define mp make_pair

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        pii out(-1, -1); int val = 1e9;
        for (int i = 1; i * i <= n; i++) {
            if (n % i)
                continue;
            int large = n - i;
            if (large % i == 0 && val > large)
                val = large, out = pii(i, large);

            int j = n / i;
            large = n - j;
            if (large > 0 && (large % j == 0 || j % large == 0) && val > max(j, large))
                val = max(j, large), out = pii(j, large);
        }
        cout << out.first << " " << out.second << "\n";
    }
}