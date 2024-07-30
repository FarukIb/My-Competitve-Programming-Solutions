#include <bits/stdc++.h>
#define mp make_pair
#define all(a) a.begin(), a.end()

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    ll n, f, t;
    cin >> n >> f >> t;

    vector<ll> arr(n);
    for (int i = 0; i < n; i++)
        cin >> arr[i];
    vector<ll> sorted = arr;
    sort(all(sorted), greater<ll>());
    if (accumulate(sorted.begin(), sorted.begin() + f, 0LL) < t)
    {
        cout << "NO\n";
        return 0;
    }
    
    vector<vector<ll> > mydp(f+1, vector<ll>(n*(n+1)/2+1));
    vector<vector<ll> > lastdp = mydp;
    ll mini = 1e9;
    for (int i = 0; i < n; i++) {
        for (int j = 1; j <= f; j++) {
            for (int s = 0; s <= n * (n + 1) / 2; s++) {
                mydp[j][s] = lastdp[j][s];
                if (s >= abs(i - (j - 1)))
                    mydp[j][s] = max(mydp[j][s], lastdp[j-1][s-abs(i - (j - 1))] + arr[i]);
                
                if (mydp[j][s] >= t and s < mini)
                    mini = s;
            }
        }
        swap(mydp, lastdp);
        fill(all(mydp), vector<ll>(n*(n+1)/2+1));
    }

    cout << mini << "\n";
}