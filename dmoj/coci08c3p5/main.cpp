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
    vector<int> l(n + 2, -1), r(n + 2, -1), depth(n + 2, -1);
    vector<int> VL(n + 2, - 1), VR(n + 2, -1);
    list<int> so_far;
    vector<list<int>::iterator> pnt(n + 2);
    for (int i = 0; i <= n + 1; i++)
        pnt[i] = so_far.insert(so_far.end(), i);
    vector<int> arr(n);
    for (int i = 0; i < n; i++)
        cin >> arr[i];
    for (int i = n - 1; i >= 0; i--) {
        VL[arr[i]] = *prev(pnt[arr[i]]), VR[arr[i]] = *next(pnt[arr[i]]);
        so_far.erase(pnt[arr[i]]);
    }

    ll sum = 0;
    for (int i = 0; i < n; i++) {
        int curr = arr[i];
        if (i == 0) {
            depth[curr] = 0;
            cout << sum << "\n";
            continue;
        }
        int vr = VR[curr], vl = VL[curr];
        if (depth[vl] > depth[vr]) {
            r[vl] = curr;
            depth[curr] = depth[vl] + 1;
        } else {
            l[vr] = curr;
            depth[curr] = depth[vr] + 1;
        }

        sum += depth[curr];
        cout << sum << "\n";
    }
}