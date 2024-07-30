#include <bits/stdc++.h>
#define mp make_pair
#define all(a) a.begin(), a.end()

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int q;
    cin >> q;
    string out;
    for (int i = 1; i < 2000; i++)
        out += to_string(i);
    while (q--) {
        ll k;
        cin >> k;
        ll num_dig = 1, num_all = 9, beg = 1;
        while (num_all*num_dig < k) {
            k -= num_all*num_dig;
            num_dig++, num_all *= 10;
            beg *= 10;
        }

        ll num = beg + (k-1)/num_dig;

        char out1 = to_string(num)[(k-1+num_dig)%num_dig];
        //if (out1 != out[k - 1])
        //    cout << "OHNO" << "\n";
        //else
            cout << out1 << "\n";
    }
}