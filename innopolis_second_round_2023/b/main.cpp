#include <bits/stdc++.h>
#define mp make_pair
#define all(a) a.begin(), a.end()
 
using namespace std;
 
typedef long long ll2;
typedef __uint128_t ll;
typedef pair<int, int> pii;
 
struct frac {
    ll p, q;
    frac() {}
    frac(ll P, ll Q) {
        if (P == 0) {
            p = 0, q = 0;
        } else {
            ll gcd = __gcd(P, Q);
            p = P / gcd;
            q = Q / gcd;
        }
    }
};
 
ll mypow(ll a, ll b){
    ll out = 1;
    for (int i = 0; i < b; i++)
        out *= a;
    return out;
}
 
const int MAXN = 2e6;
    vector<ll> primes;
 
vector<ll> get_primes(ll x) {
    int pnt = 0;
    vector<ll> prim;
    while (x > 1 and pnt < primes.size()) {
        if (x % primes[pnt] == 0)
            prim.push_back(primes[pnt]);
        while (x % primes[pnt] == 0)
            x /= primes[pnt];
        pnt++;
    }
    if (x > 1)
        prim.push_back(x);
    return prim;
}
 
ll mstoll(string a) {
    if (a.empty())
        return 0;
    return stoll(a);
}

const ll mod = 1e9 + 7;
 
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
 
    vector<bool> sito(MAXN);
    for (ll i = 2; i * i < MAXN; i++) {
        if (sito[i])
            continue;
        for (ll j = i * i; j < MAXN; j += i)
            sito[j] = true;
    }
    for (ll i = 2; i < MAXN; i++)
        if (!sito[i])
            primes.push_back(i);
 
    int n, m, k;
    cin >> n >> m >> k;
    string a, b, c;
    cin.ignore();
    getline(cin, a);
    getline(cin, b);
    getline(cin, c);
     
    frac bfrac(mstoll(b), mypow(10, m)),
        cfrac(mstoll(c), mypow(10, min(1, m))*(mypow(10, k) - 1LL));
 
    /*
    vector<ll> prim1 = get_primes(bfrac.q);
    vector<ll> prim2 = get_primes(cfrac.q);
    prim1.insert(prim1.end(), all(prim2));
    sort(all(prim1));
    prim1.erase(unique(all(prim1)), prim1.end());
    ll out = 1;
    for (ll a : prim1)
        out *= a;
    cout << out << "\n";*/
    ll lcm = bfrac.q/__gcd(bfrac.q, cfrac.q)*cfrac.q;
    frac endd;
    if (bfrac.p == 0)
        endd = cfrac;
    else if (cfrac.p == 0)
        endd = bfrac;
    else
        endd = frac(mstoll(b)*(mypow(10, k) - 1) + mstoll(c), 
        mypow(10, m)*(mypow(10, k) - 1LL));
    vector<ll> prim1 = get_primes(endd.q);
    sort(all(prim1));
    prim1.erase(unique(all(prim1)), prim1.end());
    ll out = 1;
    for (ll a : prim1)
        out *= a, out %= mod;
    cout << (ll2)out << "\n";
}