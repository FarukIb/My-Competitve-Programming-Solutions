#include <bits/stdc++.h>
#define mp make_pair
#define all(a) a.begin(), a.end()

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

int x;
struct state {
    int ride, left;
    state() {}
    state(int a, int b) {ride = a, left = b;}
    bool operator<(const state &b) const {return pii(ride, left) < pii(b.ride, b.left);}
};

state add_to(state c, int w) {
    if (c.left + w > x)
        c.left = w, c.ride++;
    else    
        c.left += w;
    return c;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int n;
    cin >> n >> x;
    vector<int> arr(n);
    for (int i = 0; i < n; i++)
        cin >> arr[i];
    vector<state> dp((1 << n), state(1e9, 1e9)); 
    dp[0] = {0, 0};
    vector<vector<int> > masks(n+1);
    for (int i = 0; i < (1 << n); i++)
        masks[__builtin_popcount(i)].push_back(i);
    for (int B = 0; B < n; B++) {
        for (int mask : masks[B]) {
            for (int i = 0; i < n; i++) {
                if (((1 << i) & mask) == 0) {
                    dp[mask + (1 << i)] = min(add_to(dp[mask], arr[i]),
                                            dp[mask + (1 << i)]);
                }
            }
        }
    }
    cout << dp[(1 << n) - 1].ride + (dp[(1 << n) - 1].left == 0 ? 0 : 1) << endl;
}