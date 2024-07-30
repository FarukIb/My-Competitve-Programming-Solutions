#include <bits/stdc++.h>
#define mp make_pair

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

const int maxn = 1e5 + 10;

bool sito[maxn];
void make_sito() {
    for (int i = 2; i * i < maxn; i++) {
        if (sito[i])
            continue;
        for (int j = i * i; j < maxn; j += i)
            sito[j] = true;
    }
}

ll bin_expo(ll base, ll expo, ll n) {
    if (expo == 0)
        return 1;
    ll half = bin_expo(base, expo / 2, n);
    half *= half, half %= n;
    if (expo % 2)
        half *= base, half %= n;
    return half;
}

ll mod_inverse(ll a, ll n) {return bin_expo(a, n - 2, n);}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    make_sito();
    int n;
    cin >> n;
    if (n == 1) {
        cout << "YES\n1\n";
        return 0;
    }
    else if (n == 4) {
        cout << "YES\n1\n3\n2\n4\n";
        return 0;
    }
    else if (sito[n]) {
        cout << "NO\n";
        return 0;
    }

    vector<int> out(n);
    out[n - 1] = n;

    out[0] = 1;
    for (int i = 1; i < n - 1; i++) {
        ll target = i + 1;
        out[i] = mod_inverse(target - 1, n) * target % n;
    }

    cout << "YES\n";
    for (int i = 0; i < n; i++)
        cout << out[i] << "\n";
}