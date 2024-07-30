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
pii,
null_type,
less<pii>,
rb_tree_tag,
tree_order_statistics_node_update>
ordered_set;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int n;
    cin >> n;
    ordered_set sett; vector<int> ans(n, 0);
    for (int i = 0; i < n; i++) {
        int x, y;
        cin >> x >> y;
        ans[sett.order_of_key({x, i})]++;
        sett.insert({x, i});
    }
    for (int a : ans)
        cout << a << "\n";
}