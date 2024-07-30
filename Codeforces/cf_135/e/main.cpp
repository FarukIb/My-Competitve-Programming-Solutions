#include <bits/stdc++.h>
#define mp make_pair

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

const ll nullval = 1e9;

int n;
int get_size(pii x) {
    if (x.first == 0)
        return (x.second - x.first);
    if (x.second == n - 1)
        return (x.second - x.first);
    return (x.second - x.first) / 2;
}

int cmp(pii a, pii b) {
    int a_size = get_size(a);
    int b_size = get_size(b);
    if (a_size > b_size)
        return true;
    else if (a_size < b_size)
        return false;
    
    return a < b;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int m;
    cin >> n >> m;
    vector<int> spaces(n + 1, nullval);
    
    
    set<pii, decltype(cmp)*> space_set(cmp);
    set<pii> int_set;
    space_set.insert(pii(0, n - 1));
    int_set.insert(pii(0, n - 1));

    map<int, int> where_is_who;

    while (m--) {
        int t, id;
        cin >> t >> id;
        
        if (t == 1) { // ARRIVING, SO INTERVAL IS SPLIT
            auto guy = space_set.begin();
            int mid = (guy->second + guy->first) / 2;
            if (guy->first == 0)
                mid = 0;
            else if (guy->second == n - 1)
                mid = n - 1;
            spaces[mid] = id;
            where_is_who[id] = mid;
        
            bool left = true, right = true;
            if (mid == 0 || spaces[mid - 1] != nullval)
                left = false;
            if (mid == n - 1 || spaces[mid + 1] != nullval)
                right = false;
            pii guy_obj = *guy;
            pii left_int(guy_obj.first, mid - 1);
            pii right_int(mid + 1, guy_obj.second);
            if (right)
            {
                space_set.insert(right_int);
                int_set.insert(right_int);
            }
            if (left) {
                space_set.insert(left_int);
                int_set.insert(left_int);
            }
            space_set.erase(guy_obj);
            int_set.erase(guy_obj);
            cout << mid + 1 << "\n";
        }
        else if (t == 2) { // LEAVING, SO INTERVAL IS MERGED
            int d = where_is_who[id];
            spaces[d] = nullval;
            bool left = true, right = true;
            if (d == 0 || spaces[d - 1] != nullval)
                left = false;
            if (d == n - 1 || spaces[d + 1] != nullval)
                right = false;
            
            auto left_int = int_set.lower_bound(pii(d, d));
            if (left_int != int_set.begin())
                left_int--;
            auto right_int = int_set.lower_bound(pii(d, d));

            pii left_int_obj = *left_int;
            pii right_int_obj = *right_int;

            pii neww;
            if (left && right)
                neww = pii(left_int->first, right_int->second);
            else if (left && !right)
                neww = pii(left_int->first, d);
            else if (right && !left)
                neww = pii(d, right_int->second);
            else if (!left && !right)
                neww = pii(d, d);

            if (left) {
                space_set.erase(left_int_obj);
                int_set.erase(left_int_obj);
            }
            if (right) {
                space_set.erase(right_int_obj);
                int_set.erase(right_int_obj);
            }

            int_set.insert(neww);
            space_set.insert(neww);
        }

    }
}