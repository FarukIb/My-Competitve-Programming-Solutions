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
greater<pii>,
rb_tree_tag,
tree_order_statistics_node_update>
ordered_set;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int n, k;
    cin >> n >> k;

    ll highj = -1, idx = 0;
    for (int j = 1; j <= k; j++) {
        ordered_set sett;

        ll my = 0;
        for (int i = 0; i < n; i++) {
            int a;
            cin >> a;
            my += sett.order_of_key({a, i});
            sett.insert({a, i});
        }

        if (my > highj) {
            highj = my, idx = j;
        }
    }

    cout << idx << "\n";
}