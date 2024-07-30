#include "gralib.hpp"
#include <bits/stdc++.h>
#define mp make_pair
#define all(a) a.begin(), a.end()

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

int main() {
    int n = dajN();
    int k = dajK();

    vector<double> dp(n+1, 1e9);
    vector<double> minval(n+1, 1e9);
    dp[n] = 0;
    for (int i = n - 1; i >= 0; i--) {
        vector<double> good;
        for (int j = 1; j <= k; j++)
            if (i % j == 0 and i + j <= n)
                good.push_back(dp[j+i]);
        sort(all(good));
        double sum = 0, minexp = 1e9, thresh = 1e9;
        for (int j = 0; j < good.size(); j++) {
            sum += good[j];
            double expected = (double) k / (double)(j + 1) + sum / (double)(j + 1);
            if (expected < minexp)
                thresh = good[j], minexp = expected;
        }
        dp[i] = minexp, minval[i] = thresh;
    }  
    for (int T = 0; T < 100; T++) {
    
    int mynum = 0;
    while (mynum != n) {
        int guy = nastepna();
        if (mynum % guy != 0 || mynum + guy > n)
            continue;
        
        if (dp[mynum + guy] <= minval[mynum]) {
            mynum += guy;
            zwieksz();
        } 
    }

    koniec();
    }
}
