#include <bits/stdc++.h>
#define mp make_pair
#define all(a) a.begin(), a.end()
 
using namespace std;
 
typedef long long ll;
typedef pair<int, int> pii;
 
const int maxn = 1e6 + 2;
vector<int> min_prim(maxn);
 
void sito() {
    for (ll i = 2; i < maxn; i++) {
        if (min_prim[i] != 0)
            continue;
        for (ll j = i ; j < maxn; j += i)
            if (min_prim[j] == 0)  
                min_prim[j] = i;
    }
}
 
vector<int> facs;
void get_small_primes(int a) {
    if (a == 1)
        return;
    facs.push_back(min_prim[a]);
    get_small_primes(a / min_prim[a]);
}
 
vector<int> get_small_factors(int a) {
    facs = vector<int>();
    get_small_primes(a);
    vector<int> factors;
    factors.push_back(1);
    vector<int> temp;
    facs.push_back(1e9); int cnt = 0;
    for (int i = 0; i < facs.size() - 1; i++) {
        cnt++;
        if (facs[i] != facs[i + 1]) {
            int val = 1;
            for (int j = 0; j < cnt; j++) {
                val *= facs[i];
                for (int a : factors)
                    temp.push_back(a * val);
            }
            factors.insert(factors.end(), all(temp));
            temp.clear();
            cnt = 0;
        }
    }
    sort(all(factors));
    return factors;
}
 
vector<int> get_big_factors(int a) {
    vector<int> factors;
    for (int i = 1; i * i <= a; i++) {
        if (i * i == a)
            factors.push_back(a);
        else if (a % i == 0)
        {
            factors.push_back(i);
            factors.push_back(a/i);
        }
    }
    sort(all(factors));
    return factors;
}
 
set<int> ans;
void recur(int n, int csum) {
    if (n == 1)
    {
        ans.insert(csum);
        return;
    }
    vector<int> factors;
    if (n < maxn)
        factors = get_small_factors(n);
    else
        factors = get_big_factors(n);
    for (int a : factors) { // the actual factor is n/a
        if (a == n)
            return;
        recur(a, csum + n/a - 1);
    }
}
 
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
 
    sito();
    int n;
    cin >> n;
    recur(n, 0);
 
    cout << ans.size() << "\n";
    for (int a : ans)
        cout << a <<" ";
    cout <<"\n";
}
