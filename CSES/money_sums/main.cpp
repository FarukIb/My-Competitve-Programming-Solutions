#include <bits/stdc++.h>
#define mp make_pair
#define all(a) a.begin(), a.end()

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int n;
    cin >> n;
    vector<int> arr(n);
    bitset<100010> dp;
    dp[0] = 1;
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        dp |= dp << x;
    }
    vector<int> out;
    for (int i = 1; i <= 100010; i++)
        if (dp[i])
            out.push_back(i);
    cout << out.size() << "\n";
    for (int i : out)
        cout << i << " ";
    cout << endl;
}