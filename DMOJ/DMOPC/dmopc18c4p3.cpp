// the editorial is a bit bad at making sense of the dynamic programming part so i will explain what i did here
// dp[0][i] = min(dp[1][i - 1] + b[i - 1], dp[0][i - 1] + a[i - 1]);
// let's analyse this expression
// dp[0][i] is the state when we are considering the first i elements and we have taken an even amount of elements from b

// dp[1][i - 1] + b[i - 1]
// if we were to say dp[0][i - 1] instead of dp[1][i - 1], then the number of elements
// taken from b in this state would be odd since adding 1 to an even number always results in an odd number

// dp[0][i - 1] + a[i - 1]

#include <algorithm>
#include <iostream>
#include <cstring>
#include <iomanip>
#include <bitset>
#include <math.h>
#include <string>
#include <vector>
#include <cmath>
#include <queue>
#include <stack>
#include <map>
#include <set>

#define pii pair<int, int>
#define ll long long

using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;

    vector<int> a(n);
    vector<int> b(n);
    for (int i = 0; i < n; i++)
        cin >> a[i];
    for (int i = 0; i < n; i++)
        cin >> b[i];
    
    vector<vector<int> > dp (2, vector<int>(n + 1, (int)1e9));
    dp[0][0] = 0;
    for (int i = 1; i <= n; i++)
    {
        dp[0][i] = min(dp[1][i - 1] + b[i - 1], dp[0][i - 1] + a[i - 1]);
        dp[1][i] = min(dp[0][i - 1] + b[i - 1], dp[1][i - 1] + a[i - 1]);
    }

    cout << dp[0][n] << endl;
}