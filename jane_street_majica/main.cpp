#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

vector<ll> primes;
vector<bool> sito;
vector<int> num_prime;

const ll maxn = 1e7;

int main() {
    
    sito = vector<bool>(maxn);
    num_prime = vector<int>(maxn);
    for (ll i = 2; i < maxn; i++) {
        if (sito[i])
            continue;
        primes.push_back(i);
        
        for (ll j = i; j < maxn; j += i)
            sito[j] = true, num_prime[j]++;
        sito[i] = false;
    }

    vector<bool> sito2(maxn);
    for (ll p : primes) {
        for (ll i = p * p; i < maxn; i += p * p)
            sito2[i] = true;
    }

    double sum = 0;
    for (ll i = 1; i < maxn; i++)
        if (!sito2[i])
            sum += 1 / ( double)(i*i);

    ll n2 = 100000;
    double sum2 = 0;
    for (ll i = 1; i <= n2; i++)
        for (ll j = 1; j <= n2; j++)
            sum2 += (1 << num_prime[__gcd(i, j)]);
    
    sum2 /= (double) n2 * (double) n2;
    cout << sum <<endl;
    cout << sum2 <<endl;
}
/*
1.51982 sum
1.51975 sum2
*/