#include <bits/stdc++.h>
#define pii pair<int, int>
#define ll long long
#define ld long double
#define mod (int)1000000007

using namespace std;

vector<int> primes;
vector<bool> sito;

void sitto(int X) {
    sito.resize(X + 1, false);

    for (int i = 2; i * i <= X; i++) {
        if (sito[i])
            continue;
        for (int j = i * i; j <= X; j += i)
            sito[j] = true;
    }

    for (int i = 2; i <= X; i++)
        if (!sito[i])
            primes.push_back(i);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    sitto(50000);
    
    vector<int> gcd_less(50001, 1);
    for (int i = 2; i <= 50000; i++) {
        ld curr = i;
        vector<int> factors;
        int x = i, c = 0;
        while (x > 1) {
            if (x % primes[c] == 0)
                factors.push_back(primes[c]);
            while (x % primes[c] == 0)
                x /= primes[c];
            c++;
        }

        for (int x : factors)
            curr *= (1.0 - 1.0 / (ld)x);
        

        gcd_less[i] = round(curr);
    }


}
