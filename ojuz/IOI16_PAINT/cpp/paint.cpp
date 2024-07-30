#include "paint.h"
#include <bits/stdc++.h>

using namespace std;

bool possible(string s, vector<int> &c) {
    
    int n = s.size(), k = c.size();
    vector<int> cumsum_white(n+1);
    for (int i = 1; i <= n; i++) {
        if (s[i - 1] == '_')
            cumsum_white[i]++;
        cumsum_white[i] += cumsum_white[i - 1];
    }

    vector<int> dp(n+1); // they are all cumsum
    vector<int> dp_last(n + 1, 1);
    for (int i = 0; i < k; i++) {
        int last_x = -1;
        for (int j = c[i]; j <= n; j++) {
            if (j != c[i] and s[j - c[i] - 1] == 'X')
                last_x = j - c[i] - 1;
            int idx1 = j - c[i];
            if (!idx1 == 0 and s[idx1 - 1] == 'X' || (j != n and s[j] == 'X'))
                continue;

            bool cond1 = (cumsum_white[j] - cumsum_white[idx1]) == 0;
            int L = last_x + 1, R = max(L, idx1 - 1);
            int sum = dp_last[R];
            if (L != 0)
                sum -= dp_last[L - 1];
            bool cond2 = sum > 0;

            if (cond1 and cond2)
                dp[j] = 1;
        }
        for (int j = 1; j <= n; j++)
            dp[j] += dp[j - 1];

        swap(dp_last, dp);
        dp = vector<int>(n+1);
    }

    int last_x = 0;
    for (int i = 0; i < n; i++)
        if (s[i] == 'X')
            last_x = i;

    return (dp_last[n] - dp_last[last_x]) > 0;
}

std::string solve_puzzle(std::string s, std::vector<int> c) {
    string out = "";
    for (int i = 0; i < s.size(); i++) {
        if (s[i] == 'X')
        {
            out += 'X';continue;
        }
        else if (s[i] == '_')
        {
            out += '_'; continue;
        }
        
        s[i] = 'X';
        bool canX = possible(s, c);
        s[i] = '_';
        bool can_ = possible(s, c);
        s[i] = '.';

        if (canX and can_)
            out += '?';
        else if (canX)
            out += 'X';
        else
            out += '_';
    }
    return out;
}
