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
tree_order_statistics_node_update> ordered_set;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);


    ordered_set sett;
    sett.insert(1);
    sett.erase(1);
    sett.lower_bound(1);

    sett.find_by_order(1);
    sett.order_of_key(2);
} 