#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#include <bits/stdc++.h>
#define mp make_pair

using namespace __gnu_pbds;
using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

typedef tree<pii, null_type, less<pii>, rb_tree_tag, tree_order_statistics_node_update> ordered_set;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int n;
    cin >> n;
    vector<int> arr(n);
    set<pii> sett;
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
        sett.insert(pii(i, arr[i]));
    }

    vector<int> out;
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        x--;

        pii curr = *sett.lower_bound(pii(x, 0));
        out.push_back(curr.second);
        sett.erase(curr);
    }

    for (int i = 0; i < n; i++)
        cout << out[i] <<" ";
    cout << "\n";
}