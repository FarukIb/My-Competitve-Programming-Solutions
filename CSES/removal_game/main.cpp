#include <bits/stdc++.h>
#define mp make_pair
#define all(a) a.begin(), a.end()

using namespace std;

typedef long long ll;
typedef pair<ll, ll> pii;

const pii null_pair = mp(-1e18, -1e18);

pii dp[5001][5001];
ll arr[5001];

pii make_dp(ll l, ll r, bool turn) {
    if (dp[l][r] != null_pair)
        return dp[l][r];
    if (l == r)
    {
        pii my(0, 0);
        if (turn)
            my.first = arr[l];
        else
            my.second = arr[r];
        return dp[l][r] = my;
    }
    pii left = make_dp(l + 1, r, !turn);
    if (turn)
        left.first += arr[l];
    else
        left.second += arr[l];
    
    pii right = make_dp(l, r - 1, !turn);
    if (turn)
        right.first += arr[r];
    else
        right.second += arr[r];
    
    if (turn) {
        if (left.first > right.first)
            return dp[l][r] = left;
        else
            return dp[l][r] = right;
    }
    else  {
        if (left.second > right.second)
            return dp[l][r] = left;
        else
            return dp[l][r] = right;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    for (int i = 0; i < 5001; i++)
        for (int j = 0; j < 5001; j++)
            dp[i][j] = null_pair;
    int n;
    cin >> n;
    for (int i = 0; i < n; i++)
        cin >> arr[i];
    cout << make_dp(0, n - 1, true).first << "\n";
}