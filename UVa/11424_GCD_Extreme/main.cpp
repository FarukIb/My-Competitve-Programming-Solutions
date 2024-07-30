#include <bits/stdc++.h>
#define pii pair<int, int>
#define ll long long
#define mx 2000001

using namespace std;

double  phi[mx];
ll ans[mx];
// O(Nlogn), less space
void sito() {
    phi[1] = 1;
    for (int i = 2; i < mx; i++) {
        if (phi[i] != 0)
            continue;
        for (int j = i; j < mx; j += i) {
            if (phi[j] == 0)
                phi[j] = j;
            phi[j] = phi[j] - phi[j] / i;
        }
    }

    for (int i = 1; i < mx; i++) 
        for (int j = i; j < mx; j += i) 
            ans[j] += (ll)phi[j / i] * i;
    for (int i = 2; i < mx; i++)    
        ans[i] += ans[i - 1];
}

// O(N) phi calc but more space
vector<int> primes;
bool sit[mx];
void sito2() {
    phi[1] = 1;
    for (int i = 2; i < mx; i++) {
        if (!sit[i]) {
            primes.push_back(i);
            phi[i] = i - 1;
        }
        for (int j = 0; j < primes.size() && i * primes[j] < mx; j++) {
            sit[i * primes[j]] = true;
            if (i % primes[j] == 0)
            {
                phi[i * primes[j]] = primes[j] * phi[i];
                break;
            }
            else
                phi[i * primes[j]] = phi[i] * phi[primes[j]];
        }
    }

    for (int i = 1; i < mx; i++) 
        for (int j = i; j < mx; j += i) 
            ans[j] += (ll)phi[j / i] * i;
    for (int i = 2; i < mx; i++)    
        ans[i] += ans[i - 1];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    sito2();
    ll x;
    while (cin >> x) {
        if (x == 0)
            break;
        cout << ans[x] - x * (x + 1) / 2 << "\n";
    } 
}
