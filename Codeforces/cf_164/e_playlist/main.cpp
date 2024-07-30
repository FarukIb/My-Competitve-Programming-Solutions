#include <bits/stdc++.h>
#define ld long double
#define pii pair<ld, ld>

using namespace std;

bool cmp(pii a, pii b) {
    return a.first * a.second / (1 - a.second) > b.first * b.second / (1 - b.second);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int n;
    cin >> n;
    vector<pii> arr(n);
    ld out = 0;
    for (int i = 0; i < n; i++)
    {
        cin >> arr[i].first >> arr[i].second;
        arr[i].second /= 100;
        out += arr[i].first;
    }

    sort(arr.begin(), arr.end(), cmp);
    ld sum = arr[0].first * arr[0].second;
    for (int i = 1;  i < n; i++) {
        out += sum * (1.0 - arr[i].second);
        sum += arr[i].first * arr[i].second;
    }

    cout << fixed << setprecision(9) << out << "\n";
}