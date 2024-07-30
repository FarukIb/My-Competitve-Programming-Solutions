#include <bits/stdc++.h>
#define pii pair<int, int>
#define ll long long
#define ld long double
#define mx 1000000

using namespace std;

vector<int> primes;
bool sito[mx];
void make() {
    for (int i = 2; i < mx; i++)
    {
        if (!sito[i])
            primes.push_back(i);
        for (int j = 0; j < primes.size() && primes[j] * i < mx; j++) {
            sito[i * primes[j]] = true;
            if (i % primes[j] == 0)
                break;
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    make();
    
    int n;
    while (cin >> n) {
        if (n == 0)
            break;

        vector<int> fact;
        int pnt = 0;
        int ans = 1;
        while (n > 1 && pnt < primes.size()) {
            if (n % primes[pnt] != 0)
            {
                pnt++;
                continue;
            }

            int c = 1;
            while (n % primes[pnt] == 0)
                c *= primes[pnt], n /= primes[pnt];

            ans *= c - c / primes[pnt];

            pnt++;
        }

        if (n != 1) {
            ans *= n - 1;
        }
        
        cout << ans << "\n";
    }
}
