#include <bits/stdc++.h>
#define mp make_pair
#define all(a) a.begin(), a.end()

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

int memo[501][501];

int dp(int i, int j) {
    if (i == j)
        return 0;
    if (memo[i][j] != 0)
        return memo[i][j];
    memo[i][j] = 1e9;
    for (int x = 1; x < i; x++)
        memo[i][j] = min(memo[i][j], 1 + dp(x, j) + dp(i-x, j));
    for (int x = 1; x < j; x++)
        memo[i][j] = min(memo[i][j], 1 + dp(i, x) + dp(i,j-x));
    return memo[i][j];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int a, b;
    cin >> a >> b;
    cout << dp(a, b) << endl;
}