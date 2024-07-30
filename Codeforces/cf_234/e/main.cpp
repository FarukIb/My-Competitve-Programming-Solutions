#include <bits/stdc++.h>
#define mp make_pair
#define int_num(l, r) (ll)(r - l + 1LL) * (ll)(r - l + 2LL) / 2LL;

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

const int maxb = 20;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int n, q;
    cin >> n >> q;
    vector<bitset<maxb> > arr(n);
    for (int i = 0; i < n; i++) {
        int a;
        cin >> a;
        arr[i] = bitset<maxb>(a);
    }
    vector<set<pii> > sett(maxb);

    ll out = 0;
    for (int b = 0; b < maxb; b++) {
        int last = -1;
        for (int i = 0; i < n; i++) {
            if (arr[i][b] == 1 and (i == 0 || arr[i - 1][b] == 0)) {
                if (last == -1)
                    last = i;
            }
            else if (arr[i][b] == 0 and i != 0 and arr[i - 1][b] == 1) {
                sett[b].insert(mp(last, i - 1));
                out += (1LL << b) * int_num(last, i - 1);
                last = -1;
            }
        }
        if (arr[n - 1][b] == 1) {
            sett[b].insert(mp(last, n - 1));
            out += (1LL << b) * int_num(last, n - 1);
        }
    }

    while (q--) {
        int p, v;
        cin >> p >> v;
        bitset<maxb> V(v);
        p--;

        for (int b = 0; b < maxb; b++) {
            if (arr[p][b] == V[b])
                continue;
            ll affected = 0;
            if (V[b] == 1) { // merges intervals
                bool has_left = true, has_right = true;
                if (p == 0 || arr[p - 1][b] == 0)
                    has_left = false;
                if (p == n - 1 || arr[p + 1][b] == 0)
                    has_right = false;
                
                if (!has_left and !has_right)
                {
                    affected = 1;
                    sett[b].insert(mp(p, p));
                }
                else if (has_right and !has_left) {
                    auto right_int = sett[b].lower_bound(mp(p, -1));
                    pii new_int(p, right_int->second);
                    affected = new_int.second - new_int.first + 1;
                    sett[b].erase(right_int);
                    sett[b].insert(new_int);
                }
                else if (!has_right and has_left) {
                    auto left_int = prev(sett[b].lower_bound(mp(p, -1)));
                    pii new_int(left_int->first, p);
                    affected = new_int.second - new_int.first + 1;
                    sett[b].erase(left_int);
                    sett[b].insert(new_int);
                } else {
                    auto right_int = sett[b].lower_bound(mp(p, -1));
                    auto left_int = prev(sett[b].lower_bound(mp(p, -1)));
                    pii new_int(left_int->first, right_int->second);
                    affected = int_num(new_int.first, new_int.second);
                    affected -= int_num(right_int->first, right_int->second);
                    affected -= int_num(left_int->first, left_int->second);
                    sett[b].erase(*right_int);
                    sett[b].erase(*left_int);
                    sett[b].insert(new_int);
                }
            } else { // splits interval
                bool has_left = true, has_right = true;
                if (p == 0 || arr[p - 1][b] == 0)
                    has_left = false;
                if (p == n - 1 || arr[p + 1][b] == 0)
                    has_right = false;
                
                if (!has_left and !has_right)
                {
                    affected = -1;
                    sett[b].erase(mp(p, p));
                }
                else if (!has_left and has_right) {
                    auto right_int = sett[b].lower_bound(mp(p, 0));
                    pii new_int(p + 1, right_int->second);
                    affected = -(new_int.second - new_int.first + 2);
                    sett[b].erase(right_int);
                    sett[b].insert(new_int);
                } else if (has_left and !has_right) {
                    auto left_int = prev(sett[b].lower_bound(mp(p, 0)));
                    pii new_int(left_int->first, p - 1);
                    affected = -(new_int.second - new_int.first + 2);
                    sett[b].erase(left_int);
                    sett[b].insert(new_int);
                } else {
                    auto interval = prev(sett[b].lower_bound(mp(p, 1e9)));
                    pii left_int(interval->first, p - 1);
                    pii right_int(p + 1, interval->second);
                    affected = -int_num(interval->first, interval->second);
                    affected += int_num(left_int.first, left_int.second);
                    affected += int_num(right_int.first, right_int.second);
                    sett[b].erase(*interval);
                    sett[b].insert(left_int);
                    sett[b].insert(right_int);
                }
            } 
            out += affected * (1LL << b);
        }
        arr[p] = V;
        cout << out << "\n";
    }
}