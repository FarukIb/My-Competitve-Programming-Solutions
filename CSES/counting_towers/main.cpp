 #include <bits/stdc++.h>
 #define mp make_pair
 #define all(a) a.begin(), a.end()
 
 using namespace std;
 
 typedef long long ll;
 typedef pair<int, int> pii;
 
 const ll mod = 1e9 + 7;

 int main() {
     ios_base::sync_with_stdio(false);
     cin.tie(0);
 
    vector<ll> dp1(1e6+1);
    vector<ll> dp2(1e6+1);
    dp1[1] = 1, dp2[1] = 1;
    for (int i = 2; i <= 1e6; i++)
        dp1[i] += (4LL*dp1[i-1]+dp2[i-1])%mod,
        dp2[i] += (dp1[i-1]+2LL*dp2[i-1])%mod;
    
    int t;
    cin >> t;
    while (t--) {
        int x;
        cin >> x;
        cout << (dp1[x]+dp2[x])%mod << "\n";
    }
 }