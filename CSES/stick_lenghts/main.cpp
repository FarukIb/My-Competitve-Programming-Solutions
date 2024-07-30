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
    vector<int> sticks(n);
    for (int i = 0; i< n; i++) 
        cin >> sticks[i];
    sort(all(sticks));
    ll mid = sticks[n/2];
    ll sum = 0;
    for (int i = 0; i < n; i++)
        sum += abs(mid - sticks[i]);
    cout << sum << "\n";
}

// 1 2 2 2