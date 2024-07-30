#include <bits/stdc++.h>
#define ld long double

using namespace std;

ld dp[1001][1001];
ld solve(ld w, ld b, bool princessTurn) {
    if (dp[(int)floor(w)][(int)floor(b)] != -1)
       return dp[(int)floor(w)][(int)floor(b)];
    if (princessTurn) {
        if (w == 0)
            return 0;
        if (b == 0)
            return 1;
        
        ld ans = w / (w + b) + b / (w + b) * solve(w, b - 1, false);
        return dp[(int)floor(w)][(int)floor(b)] = ans;
    }
    else {
        if (b == 0 || w == 0 || b == 1 && w == 1)
            return 0;
        else
        {
            if (b == 1)        
                return dp[(int)floor(w)][(int)floor(b)] = 1.0 / (1.0 + w);
            else {
                ld ans = b / (b + w) * ( 
                    (b - 1) / (b + w - 1) * solve(w, b - 2, true) + // BLACK ESCAPES
                    w * (b + w - 1) * solve(w - 1, b - 1, true) // WHITE ESCAPES
                 );
                return dp[(int)floor(w)][(int)floor(b)] = ans;
            }
        }
    }
}

int main() {
    ld w, b;
    cin >> w >> b;
    for (int i = 0; i <= w; i++)
        for (int j = 0; j <= b; j++)
            dp[i][j] = -1;

    cout << solve(w, b, true) << "\n";
}