#include <bits/stdc++.h>
#define mp make_pair
#define all(a) a.begin(), a.end()

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int n, k;
    cin >> n >> k;
    vector<pii> arr(n);
    for (int i = 0; i < n; i++)
        cin >> arr[i].second >> arr[i].first;
    sort(all(arr));
    multiset<int> endd;
    for (int i = 0; i < k; i++)
        endd.insert(0);
    int cnt = 0;
    for (int i = 0; i < n; i++) {
        auto it = endd.upper_bound(arr[i].second);
        if (it == endd.begin())
            continue;
        cnt++;
        endd.erase(prev(it));
        endd.insert(arr[i].first);
    }
    cout << cnt << endl;
}