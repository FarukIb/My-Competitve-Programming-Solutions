#include <bits/stdc++.h>
#define pii pair<int, int>
#define ll long long
#define ld long double

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector<int> arr(n);
        for (int i = 0; i < n; i++)
            cin >> arr[i];
        
        vector<bool> changed(n + 1, false);
        int changes = 0;
        arr.push_back(1e9);
        for (int i = 1; i < n - 1; i++) {
            if (arr[i] > arr[i + 1] && arr[i] > arr[i - 1]) {
                if (changed[i - 1])
                    arr[i - 1] = arr[i];
                else {
                    arr[i + 1] = max(arr[i], arr[i + 2]);
                    changes++;
                    changed[i + 1] = true;
                }
            }
        }

        cout << changes << "\n";
        for (int i = 0; i < n; i++)
            cout << arr[i] << " ";
        cout << "\n";
    }
}
