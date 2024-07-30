#include <bits/stdc++.h>
#define mp make_pair

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int n, x;
    cin >> n >> x;
    vector<int> arr(n);
    for (int i = 0; i < n; i++)
        cin >> arr[i];
    vector<int> dp(x + 1, 1e9);
    dp[0] = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = arr[i - 1]; j <= x; j++) {
            dp[j] = min(dp[j], dp[j - arr[i - 1]] + 1);
        }
    }

    if (dp[x] == 1e9)
        cout << "-1\n";
    else
        cout << dp[x] << "\n";
}