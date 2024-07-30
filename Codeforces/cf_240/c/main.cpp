#include <bits/stdc++.h>
#define mp make_pair

using namespace std;

typedef long long ll;
typedef pair<ll, ll> pii;

ll n, k;
ll sum[21];
ll tot_guy[21];

ll get_inv(vector<ll> &arr, vector<ll> &arr1, vector<ll> &arr2, ll i) {
    ll guy = 0, pnt1 = 0, pnt2 = 0;
    while (pnt1 < arr1.size() and pnt2 < arr2.size()) {
        if (arr1[pnt1] > arr2[pnt2])
        {
            arr[pnt1 + pnt2 + i] = arr2[pnt2];
            pnt2++;
            guy += arr1.size() - pnt1;
        }
        else
        {
            arr[pnt1 + pnt2 + i] = arr1[pnt1];
            pnt1++;
        }
    }
    for (; pnt1 < arr1.size(); pnt1++)
        arr[i + pnt1 + pnt2] = arr1[pnt1];
    for (; pnt2 < arr2.size(); pnt2++)
        arr[i + pnt1 + pnt2] = arr2[pnt2];

    return guy;
}

void my_merge_sort(vector<ll> &arr) {
    for (ll lvl = 1; lvl <= k; lvl++) {
        ll two_siz = 1 << lvl;
        for (ll i = 0; i + two_siz <= n; i += two_siz) {
            ll a = i, b = i + two_siz / 2, c = i + two_siz;

            vector<ll> arr1;
            for (int i = a; i < b; i++)
                arr1.push_back(arr[i]);
            vector<ll> arr2;
            for (int i = b; i < c; i++)
                arr2.push_back(arr[i]);
            ll guy = get_inv(arr, arr1, arr2, i);
            ll guy2 = get_inv(arr, arr2, arr1, i);
            
            tot_guy[lvl] += guy + guy2;
            sum[lvl] += guy;
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    ll q;
    cin >> k;
    n = 1 << k;
    vector<ll> arr(n);
    for (ll i = 0; i < n; i++)
        cin >> arr[i];
    my_merge_sort(arr);

    cin >> q;
    while (q--) {
        ll lvl;
        cin >> lvl;

        for (ll i = lvl; i >= 1; i--)
            sum[i] = tot_guy[i] - sum[i];

        ll out = 0;
        for (ll i = 1; i <= k; i++)
            out += sum[i];
        cout << out << "\n";
    }
}