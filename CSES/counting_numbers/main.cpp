 #include <bits/stdc++.h>
 #define mp make_pair
 #define all(a) a.begin(), a.end()
 
 using namespace std;
 
 typedef long long ll;
 typedef pair<int, int> pii;

 ll do_dp2(int num_digs) {
    vector<vector<vector<ll> > > dp(num_digs,
                                    vector<vector<ll> >(11,
                                    vector<ll>(2)));
    dp[0][0][0] = 1;
    ll out = 0;
    for (int i = 1; i < num_digs; i++)
        for (int dig = 0; dig <= 9; dig++)
            for (int prev = 0; prev <= 9; prev++)
                if (dig != prev)
                    dp[i][dig][0] += dp[i-1][prev][0], out += dp[i-1][prev][0];
    return out + 1;
 }

 ll do_dp(ll a) {
    if (a == -1)
        return 0;
    if (a == 0)
        return 1;
    string s = to_string(a);
    vector<vector<vector<ll> > > dp(s.size(),
                                    vector<vector<ll> >(11,
                                    vector<ll>(2)));
    for (int i = 1; i < s[0]-'0'; i++)
        dp[0][i][1] = 1;
    dp[0][s[0]-'0'][0]=1;
    for (int i = 1; i < s.size(); i++) {
        for (int dig = 0; dig <= 9; dig++) {
            if (dig > s[i] - '0') {
                for (int prev = 0; prev <= 9; prev++)
                    if (prev != dig)
                        dp[i][dig][1] += dp[i-1][prev][1];
            } else if (dig == s[i] - '0') {
                for (int prev = 0; prev <= 9; prev++)
                    if (prev != dig)
                        dp[i][dig][0] += dp[i - 1][prev][0];
                for (int prev = 0; prev <= 9; prev++)
                    if (prev != dig)
                        dp[i][dig][1] += dp[i - 1][prev][1];
            } else {
                for (int prev = 0; prev <= 9; prev++)
                    if (prev != dig)
                        dp[i][dig][1] += dp[i - 1][prev][0] + dp[i - 1][prev][1];
            }
        }
    }
    ll out = 0;
    for (int i = 0; i < 10; i++)
        out += dp[s.size()-1][i][0] + dp[s.size() - 1][i][1];
    return out + do_dp2(s.size());
}
 
 int main() {
     ios_base::sync_with_stdio(false);
     cin.tie(0);
    
    ll a, b;
    cin >>a >>b;
    cout << do_dp(b) - do_dp(a-1) << endl;
 }