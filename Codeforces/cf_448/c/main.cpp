#include <bits/stdc++.h>
#define mp make_pair
#define all(a) a.begin(), a.end()

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

const int mod = 1e9 + 7;
const int siz = 20;
vector<int> primes = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67};

int get_rep(int v) {
    int curr = 0;
    for (int i = 0; i < primes.size(); i++)
        while (v % primes[i] == 0)
            curr ^= (1 << i), v /= primes[i];
    return curr;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int n;
    cin >> n;
    vector<ll> num_way(1<<siz);
    num_way[0] = 1;
    vector<int> num(71);
    for (int i = 0; i < n; i++) {
        int v;
        cin >> v;
        num[v]++;
    }
    vector<ll> neww1(1<<siz);
    for (int i = 1; i <= 70; i++) {
        if (num[i] == 0)
            continue;
        ll num_z = 0, num_o = 1;
        for (int j = 1; j < num[i]; j++)
        {
            ll temp = num_o;
            num_o = num_z + num_o + 1;
            num_o %= mod;

            num_z = num_z + temp;
            num_z %= mod;
        }

        if (i == 1) {
            num_z = 1;
            for (int j = 0; j < num[i]; j++)
                num_z = num_z * 2LL % mod;
            num_z--;
            num_o = 0;
        }
        
        int v = get_rep(i);
        // use num_o    
        for (int i = 0; i < (1 << siz); i++)
            neww1[i] = (num_z + 1LL) * num_way[i] % mod;
        // don't
        for (int i = 0; i < (1 << siz); i++)
            neww1[i] += num_way[i ^ v] * num_o % mod, neww1[i] %= mod;
        swap(num_way, neww1);
    }
    ll out = num_way[0] - 1;
    if (out < 0)
        out += mod;
    cout << out << "\n";
}