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
    vector<int> arr(n);
    for (int i = 0; i < n; i++)
        cin >> arr[i];
    unordered_map<int, pii> mapp;
    for (int i = 0; i <n ; i++) {
        for (int j = i + 1; j < n; j++) {
            if (mapp.find(x - arr[i] - arr[j]) != mapp.end()) {
                cout << i + 1 << " " << j + 1 << " " << mapp[x - arr[i] - arr[j]].first << " " << mapp[x - arr[i] - arr[j]].second << endl;
                return 0;
            }
        }
        for (int j = i - 1; j >= 0; j--)
            mapp[arr[i] + arr[j]] = {i + 1, j + 1};
    }

    cout <<"IMPOSSIBLE" << endl;
}