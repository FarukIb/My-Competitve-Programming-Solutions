#include <iostream>
#include <algorithm>
#include <vector>
#define mp make_pair
#define all(a) a.begin(), a.end()

using namespace std;

typedef long long ll;
typedef pair<ll, ll> pii;

const ll mod = 1e9 + 7;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    ll n;
    cin >> n;
    vector<ll> arr(n + 1);

    vector<ll> fib(100);
    fib[0] = 1, fib[1] = 1;
    for (ll i = 2; i < 100; i++)
        fib[i] = fib[i - 1] + fib[i - 2];

    ll sum = 0;
    for (ll i = 0; i < n; i++)
    {
        cin >> arr[i];
        sum += fib[arr[i]];
    }

    vector<ll> mydp(sum + 1);
    vector<ll> prev(sum + 1);
    prev[0] = 1;
    for (ll i = 1; i < 100; i++) {
        if (fib[i] > sum)
            break;
        for (ll j = 0; j <= sum; j++)
        {
            mydp[j] = prev[j];
            if (j >= fib[i])
                mydp[j] += prev[j - fib[i]], mydp[j] %= mod;
        }
        swap(mydp, prev);
        fill(all(mydp), 0);
    }

    int csum = 0;
    for (int i = 0; i < n; i++) {
        csum += fib[arr[i]];
        cout << prev[csum] << "\n";
    }
}