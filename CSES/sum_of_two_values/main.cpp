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
    vector<pii> arr(n);
    for (int i = 0; i< n; i++)
    {
        cin >>arr[i].first;
        arr[i].second = i;
    }
    sort(all(arr));

    int r = n - 1;
    for (int i = 0; i < r; i++) {
        while (i < r && arr[i].first + arr[r].first > x)
            r--;
        if (arr[i].first + arr[r] .first == x and i < r) {
            cout << arr[i].second +1 << " " << arr[r].second + 1 << "\n";
            return 0;
        }
    }

    cout << "IMPOSSIBLE\n";
}