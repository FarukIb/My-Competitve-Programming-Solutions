#include <bits/stdc++.h>
#define mp make_pair
#define all(a) a.begin(), a.end()

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int n, q;
    cin >> n;
    cin >> q;
    vector<unsigned long long> arr(n);
    for (int i = 0; i < n; i++)
        cin >> arr[i];
    sort(all(arr));
    
    while (q--) {
        unsigned long long v;
        cin >> v;
        auto pnt = lower_bound(all(arr), v);
        if (pnt != arr.end() and *pnt == v)
            cout << "DA\n";
        else
            cout << "NE\n";
    }
}