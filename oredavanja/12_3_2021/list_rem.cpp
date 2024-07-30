#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp> // Common file
#include <ext/pb_ds/tree_policy.hpp> // Including tree_order_statistics_node_update
#define mp make_pair
#define all(a) a.begin(), a.end()

using namespace std;
using namespace __gnu_pbds;

typedef long long ll;
typedef pair<int, int> pii;

typedef tree<
pair<int, int>,
null_type,
less<pair<int, int> >,
rb_tree_tag,
tree_order_statistics_node_update>
ordered_set;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int n;
    cin >> n;
    int remove[n];

    ordered_set sett;

    for (int i = 0; i < n; i++) 
    {
        int temp;
        cin >> temp;
        sett.insert({i, temp});
    }

    for (int i = 0; i < n; i++) 
    {
        cin >> remove[i];
        remove[i] = remove[i]-1;
    }

    for (int i = 0; i < n; i++) 
    {
        pair<int, int> a = *sett.find_by_order(remove[i]);
        cout << a.second << " ";
        sett.erase(sett.find_by_order(remove[i]));

    }

}