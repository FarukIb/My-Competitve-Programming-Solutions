#include <bits/stdc++.h>
#define mp make_pair
#define all(a) a.begin(), a.end()

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

vector<int> do_dp(vector<int> guys) {
    int n = guys.size();
    vector<vector<int> > last(n, vector<int>(2));
    vector<vector<int> > curr(n, vector<int>(2));
    vector<int> seen(n + 1);
    for (int len = 1; len < n; len++) {
        fill(all(seen), 0);
        for (int i : guys)
            seen[i]++;
        for (int i = 0; i <= len; i++)
            seen[guys[i]]--;
        int turn = (n + 1 + len) % 2; // if true then first gets otherwise second gets
        for (int l = 0; l + len < n; l++) {
            int r = l + len;
            vector<int> ans1 = last[l + 1], ans2 = last[l];
            if (!seen[guys[l]])
                ans1[turn]++;
            if (!seen[guys[r]])
                ans2[turn]++;
            
            if (ans1[turn] > ans2[turn])
                curr[l] = ans1;
            else
                curr[l] = ans2;
            if (r != n - 1) {
                seen[guys[l]]++;
                seen[guys[r + 1]]--;
            }
        }
        swap(last, curr);
    }
    return last[0];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int n;
    cin >> n;
    vector<int> guys(n);
    for (int i = 0; i < n; i++)
        cin >> guys[i];
    if (n == 1) {
        cout << "1:0" << "\n";
        return 0;
    }
    vector<int> out = do_dp(guys);
    cout << out[0] << ":" << out[1] << "\n";
}