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
    cin >> n;
    vector<int> arr(n);
    for (int i = 0; i < n; i++)
        cin >> arr[i];
    multiset<int> op;
    op.insert(arr[0]);
    for (int i = 1; i < n; i++) {
        auto it = op.upper_bound(arr[i]);
        if (it != op.end())
            op.erase(op.upper_bound(arr[i]));
        op.insert(arr[i]);
    }

    cout << op.size() << endl;
}