#include <bits/stdc++.h>
#define mp make_pair
#define all(a) a.begin(), a.end()

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
        cin >> arr[i];

    vector<vector<int> > dp(n, vector<int>(n, 0));
    vector<int> mind_val(n, 1e9); mind_val[0] = 0;
    for (int d = 1; d < n; d++) {
        for (int i = 0; i + d < n; i++) {
            int j = i + d;

            if (d == 1)
                dp[i][j] = abs(arr[i] - arr[j]);
            else
                dp[i][j] = abs(arr[i] - arr[j]) + dp[i + 1][j - 1];
            
            mind_val[d] = min(mind_val[d], dp[i][j]);
        }
    }
    for (int i = 0; i < n; i++)
        cout << mind_val[i] <<" ";
    cout << "\n";
}