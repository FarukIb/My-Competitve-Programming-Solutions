#include <bits/stdc++.h>
#define mp make_pair
#define all(a) a.begin(), a.end()

using namespace std;

typedef long long ll;
typedef pair<ll, ll> pii;

ll intersection(pii a, pii b) {
    if (a > b)
        swap(a, b);
    return max(0LL, a.second - b.first + 1LL);
}

vector<pii> tranfs(vector<pii> arr) {
    map<int, int> sizs;
    for (auto &[l, i] : arr)
        sizs[l]++;
    vector<pii> neww;
    for (pii a : arr)
        if (sizs[a.first] == 1)
            neww.push_back(a);
    return neww;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int n;
    cin >> n;
    vector<ll> arr(n); ll sum = 0;
    for (int i = 0; i < n; i++)
    {
        cin >> arr[i];
        sum += arr[i];
    }
    sort(all(arr));
    if (arr.back() > sum - arr.back())
        cout << arr.back() * 2LL << "\n";
    else
        cout << sum << "\n";
}