#include <bits/stdc++.h>
#define mp make_pair
#define all(a) a.begin(), a.end()

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

const ll mod = 1e9 + 7;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int n;
    cin >> n;
    vector<int> ls(n), rs(n);
    for (int i = 0; i < n; i++)
        cin >> ls[i] >> rs[i];
    int max_diff = accumulate(all(rs), 0) - accumulate(all(ls), 0) + 1;
    
    
    vector dp = vector(n/2 + 1, vector<int>(max_diff*2));
    dp[0][0] = 1;
    for (int i = 1; i <= n / 2; i++) {
        int l1 = ls[i - 1], l2 = ls[n - i];
        int r1 = rs[i - 1], r2 = ls[n - i];

        for (int diff = -max_diff; diff <= max_diff; diff++) {
            
        }
    }
}