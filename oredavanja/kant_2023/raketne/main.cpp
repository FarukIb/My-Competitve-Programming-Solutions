#include <bits/stdc++.h>
#define mp make_pair

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int n;
    cin >> n;
    vector<int> arr(n);
    vector<int> diff(2, 0);

    for (int i = 0; i < n; i++)
        cin >> arr[i];
    for (int i = 0; i < n - 1; i++)
        diff.push_back(arr[i + 1] - arr[i]);
    sort(diff.begin(), diff.end());
    cout << diff[diff.size() - 2] <<"\n";
}