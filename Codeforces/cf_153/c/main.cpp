#include <bits/stdc++.h>
#define mp make_pair

using namespace std;

typedef long long ll;
typedef pair<ll, ll> pii;

ll k;
ll manual(ll a, ll b) {
    ll out = 0;
    while (a > b) {
        pii mini(a - 1, 1);
        for (ll i = 2; i <= k; i++) {
            if (a - a % i < b)
                continue;
            mini = min(mini, mp(a - a % i, -i));
        }
        //cout << a - mini.first << " " << mini.first << " " << -mini.second << "\n";
        a = mini.first;
        out++;
    }
    return out;
}

ll lcm(ll a, ll b) {return a / __gcd(a, b) * b;}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    ll a, b;
    cin >> a >> b >> k;
    ll klcm = 1;
    for (ll i = 2; i <= k; i++) 
        klcm = lcm(klcm, i);
    
    ll closest_to_a = (a / klcm) * klcm;
    ll closest_to_b = ((b / klcm) * klcm);
    if (b % klcm != 0)
        closest_to_b += klcm;

    if (closest_to_a < closest_to_b) {
        cout << manual(a, b) << "\n";
        return 0;
    }

    ll guy = manual(klcm, 0);
    ll low_part = manual(closest_to_b, b), 
    high_part = manual(a, closest_to_a), 
    between = (closest_to_a - closest_to_b) / klcm * guy;

    cout << low_part + high_part + between << "\n";
}