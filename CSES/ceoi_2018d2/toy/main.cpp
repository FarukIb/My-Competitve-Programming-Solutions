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
            factors.push_back(i);
        else if (a % i == 0)
        {
            factors.push_back(i);
            factors.push_back(a/i);
        }
    }
    sort(all(factors));
    return factors;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    sito();
    int n;
    cin >> n;
    vector<int> factors_of_n = get_big_factors(n);
    vector<vector<int> > allfac(factors_of_n.size());
    for (int i = 0; i < factors_of_n.size(); i++) {
        int a = factors_of_n[i];
        if (factors_of_n[i] > maxn)
            allfac[i] = get_big_factors(a);
        else
            allfac[i] = get_small_factors(a);
    }

    vector<vector<int>> out(factors_of_n.size());
    for (int i = 0; i < factors_of_n.size(); i++) {
        if (factors_of_n[i] == 1)
        {
            out[i] = {0};
            continue;
        }
        for (int a : allfac[i]) { // a is what's left, n/a is the factor
            if (a == factors_of_n[i])
                continue;
            int idx = lower_bound(all(factors_of_n), a) - factors_of_n.begin();
            for (int b : out[idx]) 
                out[i].push_back(b + factors_of_n[i]/a-1);
        }
        sort(all(out[i]));
        out[i].erase(unique(all(out[i])), out[i].end());
    } 
    cout << out[out.size() - 1].size() << "\n";
    for (int a : out[out.size() - 1])
        cout << a << " ";
    cout << "\n";
}