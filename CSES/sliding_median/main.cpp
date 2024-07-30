#include <bits/stdc++.h>
#include <ext/pb_ds/tree_policy.hpp>
#include <ext/pb_ds/assoc_container.hpp>
#define mp make_pair
#define all(a) a.begin(), a.end()

using namespace __gnu_pbds;
using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

typedef tree<pii, 
null_type,
less<pii>,
rb_tree_tag,
tree_order_statistics_node_update> ordered_multiset;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int n, k;
    cin >> n >> k;
    vector<int> arr(n);
    for (int i = 0; i < n; i++) 
        cin >> arr[i];
    ordered_multiset sett;
    for (int i = 0; i < k - 1; i++)
        sett.insert({arr[i], i});
    for (int i = k - 1; i < n; i++) {
        sett.insert({arr[i],i});
        cout << sett.find_by_order((k / 2) - (k+1) % 2)->first << " ";
        sett.erase(sett.lower_bound({arr[i - k + 1], 0}));
    }
    cout << endl;
}