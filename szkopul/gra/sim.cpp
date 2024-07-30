#include <bits/stdc++.h>
#define mp make_pair
#define all(a) a.begin(), a.end()

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    srand(0);
    double ans = 0;
    for (int i = 0; i < 10000; i++) {
        double cnt = 0;
        while (1) {
            cnt += 1;
            int o = rand() % 5;
            if (o == 0)
                break;
        }
        ans += cnt / 10000.0;
    }
    cout << ans << "\n";
}