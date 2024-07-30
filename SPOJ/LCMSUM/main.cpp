#include <bits/stdc++.h>
#define pii pair<int, int>
#define ll long long
#define ld long double
#define mx 1000001

using namespace std;

ll ans[mx];
ll phi[mx];
bool isprime[mx];
vector<int> primes;

void make() {
    phi[1] = 1;
    for (int i = 2; i < mx; i++) {
        if (!isprime[i]) {
            primes.push_back(i);
            phi[i] = i - 1;
        }
        for (int j = 0; j < primes.size() && primes[j] * i < mx; j++) {
            isprime[i * primes[j]] = true;
            if (i % primes[j] == 0)
            {
                phi[i * primes[j]] = phi[i] * primes[j];
                break;
            }
            else {
                phi[i * primes[j]] = phi[i] * phi[primes[j]];
            }
        }
    }

    for (int i = 2; i < mx; i++) 
    {
        for (int j = i; j < mx; j += i)
            ans[j] += i * phi[i];
        ans[i] = ((ans[i] + 2) * i) / 2;
    }
    ans[1] = 1;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    make();

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        cout << ans[n] << "\n";
    }
}
