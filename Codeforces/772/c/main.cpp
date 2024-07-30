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

        vector<int> sorted;
        sorted = arr;
        sort(sorted.begin(), sorted.end());
        if (arr == sorted) {
            cout << "0\n";
            continue;
        }
        
        if (arr[n - 2] > arr[n - 1]) {
            cout << "-1\n";
            continue;
        }

        int pos = n - 1;
        if (arr[n - 1] < 0)
        {
            cout << "-1\n";
            continue;
        }

        cout << n - 2 << "\n";
        for (int i = 0; i < n - 2; i++)
            cout << i + 1 << " " << n - 1 << " " << n << "\n";
    }
}
