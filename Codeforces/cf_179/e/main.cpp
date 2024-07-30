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
    vector<vector<int> > nums(n + 1, vector<int>());
    for (int i = 0; i < (1 << n); i++)
        nums[__builtin_popcount(i)].push_back(i);
    
    vector<vector<double>> prob(n, vector<double>(n));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            cin >> prob[i][j];
    
    vector<double> dp(1 << n, 0.0);
    dp[(1 << n) - 1] = 1;

    for (int cnt = n; cnt > 1; cnt--) {
        double prob_meeting = 1.0 / (double)(cnt *(cnt - 1) / 2);
        for (int mask : nums[cnt]) {
            vector<int> bits;
            for (int bit = 0; bit < n; bit++)
                if ((1 << bit) & mask)
                    bits.push_back(bit);
            
            for (int to_eat : bits) {
                int new_mask = mask;
                new_mask -= 1 << to_eat;
                for (int eater : bits) {
                    dp[new_mask] += prob[eater][to_eat] * dp[mask] * prob_meeting;
                }
            }
        }
    }

    for (int i = 0; i < n; i++)
        cout << dp[1 << i] << " ";
    cout << "\n";
}