#include <bits/stdc++.h>
#define mp make_pair
#define all(a) a.begin(), a.end()

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int n, k;
    cin >> n >> k;
    vector<int>mini(k+1, 1e9);
    mini[0] = 0;
    for (int i = 0; i < n; i++) {
        int co;
        cin >>co;
        for (int j = co; j <= k; j++)
            mini[j] = min(mini[j], mini[j - co] + 1);
    }
    cout << mini[k] << "\n";
}