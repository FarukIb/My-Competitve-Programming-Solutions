#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#define mp make_pair
#define all(a) a.begin(), a.end()

using namespace std;
using namespace __gnu_pbds;

typedef long long ll;
typedef pair<int, int> pii;

typedef tree<
    int,
    null_type,
    less<int>,
    rb_tree_tag,
    tree_order_statistics_node_update >
    ordered_set; 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int n, k;
    cin >> n >> k;
    ordered_set sett;
    for (int i = 0; i < n; i++)
        sett.insert(i+1);
    
    auto it = sett.find_by_order(k % n);
    for (int i = 1; i < n; i++) {
        cout << *it << " ";
        int a = sett.order_of_key(*it);
        sett.erase(*it);
        it = sett.find_by_order((a + k) % (n - i));
    }
    cout << *sett.find_by_order(0) << endl;
}