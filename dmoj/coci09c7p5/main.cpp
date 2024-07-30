#include <bits/stdc++.h>
#define mp make_pair
#define x first
#define y second
#define all(a) a.begin(), a.end()

using namespace std;

typedef long long ll;
typedef pair<ll, ll> pii;

vector<string> mat;
int r, c;
ll get_spread(vector<pii> points, char id) {
    vector<ll> ninxzone(c);
    vector<ll> suminxzone(c);

    // initializing
    vector<pii> actions; // 0 is start of inc, 1 is end of inc, 2 is start of dec, 3 is end of edc
    ll num_inc=0, num_dec=0;
    for (pii point : points) {
        ll deltay = point.x;
        ll left_bound = max(0, point.y - deltay);
        
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    cin >> r >> c;
    mat.resize(r);
    for (int i = 0; i< r; i++)
        cin >> r[i];
    
}