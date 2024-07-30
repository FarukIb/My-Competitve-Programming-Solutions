#include <bits/stdc++.h>
#define mp make_pair
#define all(a) a.begin(), a.end()

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

struct frac {
    ll p, q;
    frac() {}
    frac(ll P, ll Q) {p = P, q = Q;}
};

frac add_frac(frac a, frac b) {
    ll gcd = abs(__gcd(a.q, b.q));
    ll dem = abs(a.q / gcd * b.q);

    frac neww = {a.p * b.q / gcd + b.p * a.q / gcd, dem};
    return neww;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int n;
    cin >> n;

    vector<frac> guys;

    vector<frac> points;
    
}