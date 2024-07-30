#include <bits/stdc++.h>
#define mp make_pair
#define all(a) a.begin(), a.end()

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int n, x;
    cin >> n >> x;
    vector<int>arr(n);
    for (int i = 0; i < n; i++)
        cin >>arr[i];
    sort(all(arr));
    int cnt = 0, l = 0, r = n - 1;
    for (; l < r; l++) {
        while (l < r && arr[l] + arr[r] > x)
            r--;
        if (l < r && arr[l] + arr[r] <= x)
            cnt++, r--;
    }

    cout << n - cnt << "\n";
}