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
    cin >>n;
    vector<pii> arr(n);
    for (int i = 0; i < n; i++)
        cin >>arr[i].first >> arr[i].second;
    
    sort(all(arr));
    int r = 0;
    vector<pii> neww;
    for (pii p : arr) {
        while (!neww.empty() && neww.back().second >= p.second)
            neww.pop_back();
        neww.push_back(p);
    }

    int cnt = 0; r = 0;
    for (pii p : neww) {
        if (p.first < r)
            continue;
        cnt++, r = p.second;
    }

    cout << cnt << "\n";
}