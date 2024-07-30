#include <bits/stdc++.h>
#define mp make_pair
 
using namespace std;
 
typedef long long ll;
typedef pair<int, int> pii;
 
const ll maxn = 1e5 + 10;
const ll mod = 1e9 + 7;
ll fact[maxn];
ll invfact[maxn];
 
ll bin_expo(ll base, ll expo) {
    if (expo == 0)
        return 1;
    ll half = bin_expo(base, expo / 2); half *= half, half %= mod;
    if (expo % 2)
        half *= base, half %= mod;
    return half;
}
 
ll mod_inv(ll a) {return bin_expo(a, mod - 2); }
 
void init() {
    fact[0] = 1;
    invfact[0] = 1;
    for (ll i = 1; i < maxn; i++)
        fact[i] = fact[i - 1] * i % mod, invfact[i] = mod_inv(fact[i]);
}
 
bool lucky(ll curr) {
    string s = to_string(curr);
    for (int i = 0; i < s.size(); i++) 
        if (s[i] != '4' and s[i] != '7')
            return false;
    return true;
}
 
ll bin_coef(ll n, ll k) {
    if (n < k)
        return 0;
    return (fact[n] * invfact[k] % mod) * invfact[n - k] % mod;
}
 
ll last_dp[maxn];
ll curr_dp[maxn];
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
 
    init();
    int n, k;
    cin >> n >> k;
    ll num_lucky = 0;
    map<ll, ll> cnts;
    for (int i = 0; i < n; i++) {
        ll curr;
        cin >> curr;
        if (lucky(curr))
            cnts[curr]++, num_lucky++;
    }
    
    curr_dp[0] = 1;
    for (pii s : cnts) {
        for (int j = min(k, (int)cnts.size()); j > 0; j--)
            curr_dp[j] = (curr_dp[j] + (curr_dp[j - 1] * (ll)s.second) % mod) % mod;
        curr_dp[0] = 1;
    }
 
    ll out = 0;
    for (int i = 0; i <= k; i++)
        out += curr_dp[i] * bin_coef(n - num_lucky, k - i) % mod, out %= mod;
    cout << out << "\n";
}