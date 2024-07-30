#include <bits/stdc++.h>
#define pii pair<int, int>
#define ll long long
#define ld long double

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int n;
    cin >> n;
    vector<int> arr(n);
    for (int i = 0; i < n; i++)
        cin >> arr[i];

    int maxi = 1;
    for (int i = 0; i < n - 1; i++) {
        int q = arr[i + 1] - arr[i];
        int len = 1;
        for (int j = i + 1; j < n; j++) {
            if (arr[j] - arr[j - 1] != q)
                break;
            q = -q, len++;
        }
        maxi = max(maxi, len);
    }

    cout << maxi << "\n";
}
