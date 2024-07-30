#include <bits/stdc++.h>
#define pii pair<int, int>
#define ll long long
#define ld long double

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int n;
    while (cin >> n) {
        if (n == 0)
            break;

        int l, c;
        cin >> l >> c;
        vector<int> ts;
        vector<vector<int> > lectures;
        int cSum = 0; vector<int> cLect;
        for (int i = 0; i < n; i++) {
            int time;
            cin >> time; 
            if (cSum + time > l)
            {
                lectures.push_back(cLect);
                cSum = 0;
                cLect.clear();
            }
            cSum += time;
            cLect.push_back(time);
        }
        lectures.push_back(cLect);

        vector<ll> dp(n + 1, 0);
        
    }
}

/*
dp[i] - minimal cost for first i (i-th one hasnt given anyhting)

*/