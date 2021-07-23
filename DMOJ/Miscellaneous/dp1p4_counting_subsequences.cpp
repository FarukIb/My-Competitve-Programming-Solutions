#include <iostream>
#include <vector>
#include <math.h>
#define MOD 10007

using namespace std;

int dp[(int)1e6];

int main()
{
    string s;
    cin >> s;

    vector<int> last(30, -1);
    dp[0] = 1;

    for (int i = 1; i <= s.size(); i++)
    {
        dp[i] = 2 * dp[i - 1];

        if (last[s[i - 1] - 'a'] != -1)
            dp[i] -= dp[last[s[i - 1] - 'a']];
        if (dp[i] < 0)
            dp[i] += MOD;
        dp[i] %= MOD;
        
        last[s[i - 1] - 'a'] = i - 1;
    }

    cout << dp[s.size()] - 1 << endl; // the - 1 is to account for the emtpy subsequence
}